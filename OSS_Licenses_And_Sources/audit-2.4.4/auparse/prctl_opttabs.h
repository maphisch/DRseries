/* This is a generated file, see Makefile.am for its inputs. */
static const char prctl_opt_strings[] = "PR_CAPBSET_DROP\0PR_CAPBSET_READ\0PR_GET_CHILD_SUBREAPER\0PR_GET_DUMPABLE\0PR_GET_ENDIAN\0PR_GET_FPEMU\0PR_GET_FPEXC\0PR_GET_FP_MODE\0PR_GET_KEEPCAPS\0PR_GET_NAME\0"
	"PR_GET_NO_NEW_PRIVS\0PR_GET_PDEATHSIG\0PR_GET_SECCOMP\0PR_GET_SECUREBITS\0PR_GET_THP_DISABLE\0PR_GET_TID_ADDRESS\0PR_GET_TIMERSLACK\0PR_GET_TIMING\0PR_GET_TSC\0PR_GET_UNALIGN\0"
	"PR_MCE_KILL\0PR_MCE_KILL_GET\0PR_MPX_DISABLE_MANAGEMENT\0PR_MPX_ENABLE_MANAGEMENT\0PR_SET_CHILD_SUBREAPER\0PR_SET_DUMPABLE\0PR_SET_ENDIAN\0PR_SET_FPEMU\0PR_SET_FPEXC\0PR_SET_FP_MODE\0"
	"PR_SET_KEEPCAPS\0PR_SET_MM\0PR_SET_NAME\0PR_SET_NO_NEW_PRIVS\0PR_SET_PDEATHSIG\0PR_SET_SECCOMP\0PR_SET_SECUREBITS\0PR_SET_THP_DISABLE\0PR_SET_TIMERSLACK\0PR_SET_TIMING\0"
	"PR_SET_TSC\0PR_SET_UNALIGN\0PR_TASK_PERF_EVENTS_DISABLE\0PR_TASK_PERF_EVENTS_ENABLE";
static const unsigned prctl_opt_i2s_direct[] = {
	551,174,55,422,305,663,126,493,85,452,
	98,465,280,638,519,142,-1u,-1u,71,438,
	191,568,16,0,294,652,206,583,620,262,
	678,706,320,332,509,399,32,531,154,243,
	601,224,374,348,478,111,
};
static const char *prctl_opt_i2s(int v) {
	return i2s_direct__(prctl_opt_strings, prctl_opt_i2s_direct, 1, 46, v);
}