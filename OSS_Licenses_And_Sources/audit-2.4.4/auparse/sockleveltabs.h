/* This is a generated file, see Makefile.am for its inputs. */
static const char socklevel_strings[] = "SOL_AAL\0SOL_ALG\0SOL_ATALK\0SOL_ATM\0SOL_AX25\0SOL_BLUETOOTH\0SOL_CAIF\0SOL_DCCP\0SOL_DECNET\0SOL_ICMPV6\0"
	"SOL_IP\0SOL_IPV6\0SOL_IPX\0SOL_IRDA\0SOL_IUCV\0SOL_LLC\0SOL_NETBEUI\0SOL_NETLINK\0SOL_NETROM\0SOL_NFC\0"
	"SOL_PACKET\0SOL_PNPIPE\0SOL_PPPOL2TP\0SOL_RAW\0SOL_RDS\0SOL_ROSE\0SOL_RXRPC\0SOL_SCTP\0SOL_TCP\0SOL_TIPC\0"
	"SOL_UDP\0SOL_UDPLITE";
static const int socklevel_i2s_i[] = {
	0,6,17,41,58,132,136,255,256,257,
	258,259,260,261,263,264,265,266,267,268,
	269,270,271,272,273,274,275,276,277,278,
	279,280,
};
static const unsigned socklevel_i2s_s[] = {
	97,269,286,104,86,260,294,225,113,34,
	16,171,241,75,190,26,0,121,147,139,
	66,159,277,250,212,43,201,233,130,57,
	8,182,
};
static const char *socklevel_i2s(int v) {
	return i2s_bsearch__(socklevel_strings, socklevel_i2s_i, socklevel_i2s_s, 32, v);
}
