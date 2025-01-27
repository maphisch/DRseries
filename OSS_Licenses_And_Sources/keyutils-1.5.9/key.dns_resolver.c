/*
 * DNS Resolver Module User-space Helper for AFSDB records
 *
 * Copyright (C) Wang Lei (wang840925@gmail.com) 2010
 * Authors: Wang Lei (wang840925@gmail.com)
 *          David Howells (dhowells@redhat.com)
 *
 * This is a userspace tool for querying AFSDB RR records in the DNS on behalf
 * of the kernel, and converting the VL server addresses to IPv4 format so that
 * they can be used by the kAFS filesystem.
 *
 * Compile with:
 *
 * 	cc -o key.dns_resolver key.dns_resolver.c -lresolv -lkeyutils
 *
 * As some function like res_init() should use the static liberary, which is a
 * bug of libresolv, that is the reason for cifs.upcall to reimplement.
 *
 * To use this program, you must tell /sbin/request-key how to invoke it.  You
 * need to have the keyutils package installed and something like the following
 * lines added to your /etc/request-key.conf file:
 *
 * 	#OP    TYPE         DESCRIPTION CALLOUT INFO PROGRAM ARG1 ARG2 ARG3 ...
 * 	====== ============ =========== ============ ==========================
 * 	create dns_resolver afsdb:*     *            /sbin/key.dns_resolver %k
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#define _GNU_SOURCE
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <keyutils.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

static const char *DNS_PARSE_VERSION = "1.0";
static const char prog[] = "key.dns_resolver";
static const char key_type[] = "dns_resolver";
static const char a_query_type[] = "a";
static const char aaaa_query_type[] = "aaaa";
static const char afsdb_query_type[] = "afsdb";
static key_serial_t key;
static int verbose;
static int debug_mode;


#define	MAX_VLS			15	/* Max Volume Location Servers Per-Cell */
#define	INET_IP4_ONLY		0x1
#define	INET_IP6_ONLY		0x2
#define	INET_ALL		0xFF
#define ONE_ADDR_ONLY		0x100

/*
 * segmental payload
 */
#define N_PAYLOAD 256
struct iovec payload[N_PAYLOAD];
int payload_index;

/*
 * Print an error to stderr or the syslog, negate the key being created and
 * exit
 */
static __attribute__((format(printf, 1, 2), noreturn))
void error(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	if (isatty(2)) {
		vfprintf(stderr, fmt, va);
		fputc('\n', stderr);
	} else {
		vsyslog(LOG_ERR, fmt, va);
	}
	va_end(va);

	/*
	 * on error, negatively instantiate the key ourselves so that we can
	 * make sure the kernel doesn't hang it off of a searchable keyring
	 * and interfere with the next attempt to instantiate the key.
	 */
	if (!debug_mode)
		keyctl_negate(key, 1, KEY_REQKEY_DEFL_DEFAULT);

	exit(1);
}

#define error(FMT, ...) error("Error: " FMT, ##__VA_ARGS__);

/*
 * Just print an error to stderr or the syslog
 */
static __attribute__((format(printf, 1, 2)))
void _error(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	if (isatty(2)) {
		vfprintf(stderr, fmt, va);
		fputc('\n', stderr);
	} else {
		vsyslog(LOG_ERR, fmt, va);
	}
	va_end(va);
}

/*
 * Print status information
 */
static __attribute__((format(printf, 1, 2)))
void info(const char *fmt, ...)
{
	va_list va;

	if (verbose < 1)
		return;

	va_start(va, fmt);
	if (isatty(1)) {
		fputs("I: ", stdout);
		vfprintf(stdout, fmt, va);
		fputc('\n', stdout);
	} else {
		vsyslog(LOG_INFO, fmt, va);
	}
	va_end(va);
}

/*
 * Print a nameserver error and exit
 */
static const int ns_errno_map[] = {
	[0]			= ECONNREFUSED,
	[HOST_NOT_FOUND]	= ENODATA,
	[TRY_AGAIN]		= EAGAIN,
	[NO_RECOVERY]		= ECONNREFUSED,
	[NO_DATA]		= ENODATA,
};

static __attribute__((noreturn))
void nsError(int err, const char *domain)
{
	unsigned timeout = 1 * 60;
	int ret;

	if (isatty(2))
		fprintf(stderr, "%s: %s.\n", domain, hstrerror(err));
	else
		syslog(LOG_INFO, "%s: %s", domain, hstrerror(err));

	if (err >= sizeof(ns_errno_map) / sizeof(ns_errno_map[0]))
		err = ECONNREFUSED;
	else
		err = ns_errno_map[err];

	info("Reject the key with error %d", err);

	if (err == EAGAIN)
		timeout = 1;
	else if (err == ECONNREFUSED)
		timeout = 10;

	if (!debug_mode) {
		ret = keyctl_reject(key, timeout, err, KEY_REQKEY_DEFL_DEFAULT);
		if (ret == -1)
			error("%s: keyctl_reject: %m", __func__);
	}
	exit(0);
}

/*
 * Print debugging information
 */
static __attribute__((format(printf, 1, 2)))
void debug(const char *fmt, ...)
{
	va_list va;

	if (verbose < 2)
		return;

	va_start(va, fmt);
	if (isatty(1)) {
		fputs("D: ", stdout);
		vfprintf(stdout, fmt, va);
		fputc('\n', stdout);
	} else {
		vsyslog(LOG_DEBUG, fmt, va);
	}
	va_end(va);
}

/*
 * Append an address to the payload segment list
 */
static void append_address_to_payload(const char *addr)
{
	size_t sz = strlen(addr);
	char *copy;
	int loop;

	debug("append '%s'", addr);

	if (payload_index + 2 > N_PAYLOAD - 1)
		return;

	/* discard duplicates */
	for (loop = 0; loop < payload_index; loop++)
		if (payload[loop].iov_len == sz &&
		    memcmp(payload[loop].iov_base, addr, sz) == 0)
			return;

	copy = malloc(sz);
	if (!copy)
		error("%s: malloc: %m", __func__);
	memcpy(copy, addr, sz);

	if (payload_index != 0) {
		payload[payload_index  ].iov_base = ",";
		payload[payload_index++].iov_len = 1;
	}
	payload[payload_index  ].iov_base = copy;
	payload[payload_index++].iov_len = sz;
}

/*
 * Dump the payload when debugging
 */
static void dump_payload(void)
{
	size_t plen, n;
	char *buf, *p;
	int loop;

	if (debug_mode)
		verbose = 1;
	if (verbose < 1)
		return;

	plen = 0;
	for (loop = 0; loop < payload_index; loop++) {
		n = payload[loop].iov_len;
		debug("seg[%d]: %zu", loop, n);
		plen += n;
	}
	if (plen == 0) {
		info("The key instantiation data is empty");
		return;
	}

	debug("total: %zu", plen);
	buf = malloc(plen + 1);
	if (!buf)
		return;

	p = buf;
	for (loop = 0; loop < payload_index; loop++) {
		n = payload[loop].iov_len;
		memcpy(p, payload[loop].iov_base, n);
		p += n;
	}

	info("The key instantiation data is '%s'", buf);
	free(buf);
}

/*
 * Perform address resolution on a hostname and add the resulting address as a
 * string to the list of payload segments.
 */
static int
dns_resolver(const char *server_name, unsigned mask)
{
	struct addrinfo hints, *addr, *ai;
	char buf[INET6_ADDRSTRLEN + 1];
	int ret, len;
	void *sa;

	debug("Resolve '%s' with %x", server_name, mask);

	memset(&hints, 0, sizeof(hints));
	switch (mask & INET_ALL) {
	case INET_IP4_ONLY:	hints.ai_family = AF_INET;	debug("IPv4"); break;
	case INET_IP6_ONLY:	hints.ai_family = AF_INET6;	debug("IPv6"); break;
	default: break;
	}

	/* resolve name to ip */
	ret = getaddrinfo(server_name, NULL, &hints, &addr);
	if (ret) {
		info("unable to resolve hostname: %s [%s]",
		     server_name, gai_strerror(ret));
		return -1;
	}

	debug("getaddrinfo = %d", ret);

	for (ai = addr; ai; ai = ai->ai_next) {
		debug("RR: %x,%x,%x,%x,%x,%s",
		      ai->ai_flags, ai->ai_family,
		      ai->ai_socktype, ai->ai_protocol,
		      ai->ai_addrlen, ai->ai_canonname);

		/* convert address to string */
		switch (ai->ai_family) {
		case AF_INET:
			if (!(mask & INET_IP4_ONLY))
				continue;
			sa = &(((struct sockaddr_in *)ai->ai_addr)->sin_addr);
			len = INET_ADDRSTRLEN;
			break;
		case AF_INET6:
			if (!(mask & INET_IP6_ONLY))
				continue;
			sa = &(((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr);
			len = INET6_ADDRSTRLEN;
			break;
		default:
			debug("Address of unknown family %u", addr->ai_family);
			continue;
		}

		if (!inet_ntop(ai->ai_family, sa, buf, len))
			error("%s: inet_ntop: %m", __func__);

		append_address_to_payload(buf);
		if (mask & ONE_ADDR_ONLY)
			break;
	}

	freeaddrinfo(addr);
	return 0;
}

/*
 *
 */
static void afsdb_hosts_to_addrs(ns_msg handle,
				 ns_sect section,
				 unsigned mask,
				 unsigned long *_ttl)
{
	char *vllist[MAX_VLS];	/* list of name servers	*/
	int vlsnum = 0;		/* number of name servers in list */
	int rrnum;
	ns_rr rr;
	int subtype, i, ret;
	unsigned int ttl = UINT_MAX, rr_ttl;

	debug("AFSDB RR count is %d", ns_msg_count(handle, section));

	/* Look at all the resource records in this section. */
	for (rrnum = 0; rrnum < ns_msg_count(handle, section); rrnum++) {
		/* Expand the resource record number rrnum into rr. */
		if (ns_parserr(&handle, section, rrnum, &rr)) {
			_error("ns_parserr failed : %m");
			continue;
		}

		/* We're only interested in AFSDB records */
		if (ns_rr_type(rr) == ns_t_afsdb) {
			vllist[vlsnum] = malloc(MAXDNAME);
			if (!vllist[vlsnum])
				error("Out of memory");

			subtype = ns_get16(ns_rr_rdata(rr));

			/* Expand the name server's domain name */
			if (ns_name_uncompress(ns_msg_base(handle),
					       ns_msg_end(handle),
					       ns_rr_rdata(rr) + 2,
					       vllist[vlsnum],
					       MAXDNAME) < 0)
				error("ns_name_uncompress failed");

			rr_ttl = ns_rr_ttl(rr);
			if (ttl > rr_ttl)
				ttl = rr_ttl;

			/* Check the domain name we've just unpacked and add it to
			 * the list of VL servers if it is not a duplicate.
			 * If it is a duplicate, just ignore it.
			 */
			for (i = 0; i < vlsnum; i++)
				if (strcasecmp(vllist[i], vllist[vlsnum]) == 0)
					goto next_one;

			/* Turn the hostname into IP addresses */
			ret = dns_resolver(vllist[vlsnum], mask);
			if (ret) {
				debug("AFSDB RR can't resolve."
				      "subtype:%d, server name:%s, netmask:%u",
				      subtype, vllist[vlsnum], mask);
				goto next_one;
			}

			info("AFSDB RR subtype:%d, server name:%s, ip:%*.*s, ttl:%u",
			     subtype, vllist[vlsnum],
			     (int)payload[payload_index - 1].iov_len,
			     (int)payload[payload_index - 1].iov_len,
			     (char *)payload[payload_index - 1].iov_base,
			     ttl);

			/* prepare for the next record */
			vlsnum++;
			continue;

		next_one:
			free(vllist[vlsnum]);
		}
	}

	*_ttl = ttl;
	info("ttl: %u", ttl);
}

/*
 * Look up an AFSDB record to get the VL server addresses.
 *
 * The callout_info is parsed for request options.  For instance, "ipv4" to
 * request only IPv4 addresses and "ipv6" to request only IPv6 addresses.
 */
static __attribute__((noreturn))
int dns_query_afsdb(const char *cell, char *options)
{
	int	ret;
	unsigned mask = INET_ALL;
	int	response_len;		/* buffer length */
	ns_msg	handle;			/* handle for response message */
	unsigned long ttl = ULONG_MAX;
	union {
		HEADER hdr;
		u_char buf[NS_PACKETSZ];
	} response;		/* response buffers */

	debug("Get AFSDB RR for cell name:'%s', options:'%s'", cell, options);

	/* query the dns for an AFSDB resource record */
	response_len = res_query(cell,
				 ns_c_in,
				 ns_t_afsdb,
				 response.buf,
				 sizeof(response));

	if (response_len < 0)
		/* negative result */
		nsError(h_errno, cell);

	if (ns_initparse(response.buf, response_len, &handle) < 0)
		error("ns_initparse: %m");

	/* Is the IP address family limited? */
	if (strcmp(options, "ipv4") == 0)
		mask = INET_IP4_ONLY;
	else if (strcmp(options, "ipv6") == 0)
		mask = INET_IP6_ONLY;

	/* look up the hostnames we've obtained to get the actual addresses */
	afsdb_hosts_to_addrs(handle, ns_s_an, mask, &ttl);

	info("DNS query AFSDB RR results:%u ttl:%lu", payload_index, ttl);

	/* set the key's expiry time from the minimum TTL encountered */
	if (!debug_mode) {
		ret = keyctl_set_timeout(key, ttl);
		if (ret == -1)
			error("%s: keyctl_set_timeout: %m", __func__);
	}

	/* handle a lack of results */
	if (payload_index == 0)
		nsError(NO_DATA, cell);

	/* must include a NUL char at the end of the payload */
	payload[payload_index].iov_base = "";
	payload[payload_index++].iov_len = 1;
	dump_payload();

	/* load the key with data key */
	if (!debug_mode) {
		ret = keyctl_instantiate_iov(key, payload, payload_index, 0);
		if (ret == -1)
			error("%s: keyctl_instantiate: %m", __func__);
	}

	exit(0);
}

/*
 * Look up a A and/or AAAA records to get host addresses
 *
 * The callout_info is parsed for request options.  For instance, "ipv4" to
 * request only IPv4 addresses, "ipv6" to request only IPv6 addresses and
 * "list" to get multiple addresses.
 */
static __attribute__((noreturn))
int dns_query_a_or_aaaa(const char *hostname, char *options)
{
	unsigned mask;
	int ret;

	debug("Get A/AAAA RR for hostname:'%s', options:'%s'",
	      hostname, options);

	if (!options[0]) {
		/* legacy mode */
		mask = INET_IP4_ONLY | ONE_ADDR_ONLY;
	} else {
		char *k, *val;

		mask = INET_ALL | ONE_ADDR_ONLY;

		do {
			k = options;
			options = strchr(options, ' ');
			if (!options)
				options = k + strlen(k);
			else
				*options++ = '\0';
			if (!*k)
				continue;
			if (strchr(k, ','))
				error("Option name '%s' contains a comma", k);

			val = strchr(k, '=');
			if (val)
				*val++ = '\0';

			debug("Opt %s", k);

			if (strcmp(k, "ipv4") == 0) {
				mask &= ~INET_ALL;
				mask |= INET_IP4_ONLY;
			} else if (strcmp(k, "ipv6") == 0) {
				mask &= ~INET_ALL;
				mask |= INET_IP6_ONLY;
			} else if (strcmp(k, "list") == 0) {
				mask &= ~ONE_ADDR_ONLY;
			}

		} while (*options);
	}

	/* Turn the hostname into IP addresses */
	ret = dns_resolver(hostname, mask);
	if (ret)
		nsError(NO_DATA, hostname);

	/* handle a lack of results */
	if (payload_index == 0)
		nsError(NO_DATA, hostname);

	/* must include a NUL char at the end of the payload */
	payload[payload_index].iov_base = "";
	payload[payload_index++].iov_len = 1;
	dump_payload();

	/* load the key with data key */
	if (!debug_mode) {
		ret = keyctl_instantiate_iov(key, payload, payload_index, 0);
		if (ret == -1)
			error("%s: keyctl_instantiate: %m", __func__);
	}

	exit(0);
}

/*
 * Print usage details,
 */
static __attribute__((noreturn))
void usage(void)
{
	if (isatty(2)) {
		fprintf(stderr,
			"Usage: %s [-vv] key_serial\n",
			prog);
		fprintf(stderr,
			"Usage: %s -D [-vv] <desc> <calloutinfo>\n",
			prog);
	} else {
		info("Usage: %s [-vv] key_serial", prog);
	}
	exit(2);
}

const struct option long_options[] = {
	{ "debug",	0, NULL, 'D' },
	{ "verbose",	0, NULL, 'v' },
	{ "version",	0, NULL, 'V' },
	{ NULL,		0, NULL, 0 }
};

/*
 *
 */
int main(int argc, char *argv[])
{
	int ktlen, qtlen, ret;
	char *keyend, *p;
	char *callout_info = NULL;
	char *buf = NULL, *name;

	openlog(prog, 0, LOG_DAEMON);

	while ((ret = getopt_long(argc, argv, "vD", long_options, NULL)) != -1) {
		switch (ret) {
		case 'D':
			debug_mode = 1;
			continue;
		case 'V':
			printf("version: %s from %s (%s)\n",
			       DNS_PARSE_VERSION,
			       keyutils_version_string,
			       keyutils_build_string);
			exit(0);
		case 'v':
			verbose++;
			continue;
		default:
			if (!isatty(2))
				syslog(LOG_ERR, "unknown option: %c", ret);
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (!debug_mode) {
		if (argc != 1)
			usage();

		/* get the key ID */
		if (!**argv)
			error("Invalid blank key ID");
		key = strtol(*argv, &p, 10);
		if (*p)
			error("Invalid key ID format");

		/* get the key description (of the form "x;x;x;x;<query_type>:<name>") */
		ret = keyctl_describe_alloc(key, &buf);
		if (ret == -1)
			error("keyctl_describe_alloc failed: %m");

		/* get the callout_info (which can supply options) */
		ret = keyctl_read_alloc(KEY_SPEC_REQKEY_AUTH_KEY, (void **)&callout_info);
		if (ret == -1)
			error("Invalid key callout_info read: %m");
	} else {
		if (argc != 2)
			usage();

		ret = asprintf(&buf, "%s;-1;-1;0;%s", key_type, argv[0]);
		if (ret < 0)
			error("Error %m");
		callout_info = argv[1];
	}

	ret = 1;
	info("Key description: '%s'", buf);
	info("Callout info: '%s'", callout_info);

	p = strchr(buf, ';');
	if (!p)
		error("Badly formatted key description '%s'", buf);
	ktlen = p - buf;

	/* make sure it's the type we are expecting */
	if (ktlen != sizeof(key_type) - 1 ||
	    memcmp(buf, key_type, ktlen) != 0)
		error("Key type is not supported: '%*.*s'", ktlen, ktlen, buf);

	keyend = buf + ktlen + 1;

	/* the actual key description follows the last semicolon */
	keyend = rindex(keyend, ';');
	if (!keyend)
		error("Invalid key description: %s", buf);
	keyend++;

	name = index(keyend, ':');
	if (!name)
		dns_query_a_or_aaaa(keyend, callout_info);

	qtlen = name - keyend;
	name++;

	if ((qtlen == sizeof(a_query_type) - 1 &&
	     memcmp(keyend, a_query_type, sizeof(a_query_type) - 1) == 0) ||
	    (qtlen == sizeof(aaaa_query_type) - 1 &&
	     memcmp(keyend, aaaa_query_type, sizeof(aaaa_query_type) - 1) == 0)
	    ) {
		info("Do DNS query of A/AAAA type for:'%s' mask:'%s'",
		     name, callout_info);
		dns_query_a_or_aaaa(name, callout_info);
	}

	if (qtlen == sizeof(afsdb_query_type) - 1 &&
	    memcmp(keyend, afsdb_query_type, sizeof(afsdb_query_type) - 1) == 0
	    ) {
		info("Do DNS query of AFSDB type for:'%s' mask:'%s'",
		     name, callout_info);
		dns_query_afsdb(name, callout_info);
	}

	error("Query type: \"%*.*s\" is not supported", qtlen, qtlen, keyend);
}
