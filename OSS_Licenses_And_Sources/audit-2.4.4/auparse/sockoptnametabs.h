/* This is a generated file, see Makefile.am for its inputs. */
static const char sockoptname_strings[] = "SO_ACCEPTCONN\0SO_ATTACH_BPF\0SO_ATTACH_FILTER\0SO_BINDTODEVICE\0SO_BPF_EXTENSIONS\0SO_BROADCAST\0SO_BSDCOMPAT\0SO_BUSY_POLL\0SO_DEBUG\0SO_DETACH_FILTER\0"
	"SO_DOMAIN\0SO_DONTROUTE\0SO_ERROR\0SO_INCOMING_CPU\0SO_KEEPALIVE\0SO_LINGER\0SO_LOCK_FILTER\0SO_MARK\0SO_MAX_PACING_RATE\0SO_NOFCS\0"
	"SO_NO_CHECK\0SO_OOBINLINE\0SO_PASSCRED\0SO_PASSCRED\0SO_PASSSEC\0SO_PEEK_OFF\0SO_PEERCRED\0SO_PEERCRED\0SO_PEERNAME\0SO_PEERSEC\0"
	"SO_PRIORITY\0SO_PROTOCOL\0SO_RCVBUF\0SO_RCVBUFFORCE\0SO_RCVLOWAT\0SO_RCVLOWAT\0SO_RCVTIMEO\0SO_RCVTIMEO\0SO_REUSEADDR\0SO_REUSEPORT\0"
	"SO_RXQ_OVFL\0SO_SECURITY_AUTHENTICATION\0SO_SECURITY_ENCRYPTION_NETWORK\0SO_SECURITY_ENCRYPTION_TRANSPORT\0SO_SELECT_ERR_QUEUE\0SO_SNDBUF\0SO_SNDBUFFORCE\0SO_SNDLOWAT\0SO_SNDLOWAT\0SO_SNDTIMEO\0"
	"SO_SNDTIMEO\0SO_TIMESTAMP\0SO_TIMESTAMPING\0SO_TIMESTAMPNS\0SO_TYPE\0SO_WIFI_STATUS";
static const int sockoptname_i2s_i[] = {
	1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16,17,18,19,20,
	21,22,23,24,25,26,27,28,29,30,
	31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,
	116,117,118,119,120,121,
};
static const unsigned sockoptname_i2s_s[] = {
	118,482,748,167,154,79,631,409,192,278,
	266,385,205,92,495,291,338,434,656,458,
	680,520,578,547,45,28,127,362,704,0,
	374,641,419,315,733,230,717,397,144,508,
	756,326,257,215,611,105,238,61,176,14,
	446,668,470,692,303,350,
};
static const char *sockoptname_i2s(int v) {
	return i2s_bsearch__(sockoptname_strings, sockoptname_i2s_i, sockoptname_i2s_s, 56, v);
}
