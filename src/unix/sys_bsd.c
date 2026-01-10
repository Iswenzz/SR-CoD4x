#include "../q_shared.h"
#include "../q_platform.h"

#ifdef __BSD__

	#include "../qcommon_mem.h"
	#include "../qcommon_io.h"
	#include "../qcommon.h"
	#include "../sys_main.h"
	#include "../cmd.h"
	#include "../sys_cod4defs.h"
	#include "../sec_crypto.h"
	#include "../sec_common.h"
	#include "sys_unix.h"

	#include <sys/resource.h>
	#include <libgen.h>
	#include <signal.h>
	#include <sys/mman.h>
	#include <string.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <dlfcn.h>
	#include <dirent.h>
	#include <sys/stat.h>
	#include <pwd.h>
	#include <execinfo.h>
	#include <sys/wait.h>
	#include <sys/sysctl.h>
	#include <pthread.h>
	#include <pthread_np.h>

static char homePath[MAX_OSPATH];

const char *Sys_DefaultHomePath(void)
{
	char *p;

	if (!*homePath)
	{
		if ((p = getenv("HOME")) != NULL)
		{
			Com_sprintf(homePath, sizeof(homePath), "%s%c", p, PATH_SEP);
			Q_strncat(homePath, sizeof(homePath), HOMEPATH_NAME_UNIX);
		}
	}

	return homePath;
}

const char *Sys_TempPath(void)
{
	const char *TMPDIR = getenv("TMPDIR");

	if (TMPDIR == NULL || TMPDIR[0] == '\0')
		return "/tmp";
	else
		return TMPDIR;
}

void Sys_PrintBacktrace(void *ctx)
{
	void **traces;
	char **symbols;
	int numFrames;
	int i;
	Com_Printf(CON_CHANNEL_SR_DEBUG, "---------- Backtrace ----------\n");
	traces = malloc(65536 * sizeof(void *));
	numFrames = backtrace(traces, 65536);
	symbols = backtrace_symbols(traces, numFrames);
	for (i = 0; i < numFrames; i++)
		Com_Printf(CON_CHANNEL_SR_DEBUG, "%5d: %s\n", numFrames - i - 1, symbols[i]);
	free(traces);
}

void Sys_DumpCrash(int signal, struct sigcontext *ctx)
{
	char hash[65];
	long unsigned size = sizeof(hash);

	Com_Printf(CON_CHANNEL_SR_DEBUG, "This program has crashed with signal: %s\n", strsignal(signal));
	Com_Printf(CON_CHANNEL_SR_DEBUG, "The current Gameversion is: %s %s %s build %i %s\n", GAME_STRING, Q3_VERSION,
		PLATFORM_STRING, BUILD_NUMBER, __DATE__);
	Sec_HashFile(SEC_HASH_SHA256, Sys_ExeFile(), hash, &size, qfalse);
	// Q_strncpyz(hash, "File Hashing has not been implemented yet", sizeof(hash));
	hash[64] = '\0';
	Com_Printf(CON_CHANNEL_SR_DEBUG, "File is %s Hash is: %s\n", Sys_ExeFile(), hash);
	Sys_PrintBacktrace(null);
	Com_Printf(CON_CHANNEL_SR_DEBUG, "\n-- Registers ---\n");
	Com_Printf(CON_CHANNEL_SR_DEBUG,
		"edi 0x%lx\nesi 0x%lx\nebp 0x%lx\nesp 0x%lx\neax 0x%lx\nebx 0x%lx\necx 0x%lx\nedx 0x%lu\neip 0x%lx\n",
		ctx->sc_edi, ctx->sc_esi, ctx->sc_ebp, ctx->sc_esp, ctx->sc_eax, ctx->sc_ebx, ctx->sc_ecx, ctx->sc_edx,
		ctx->sc_eip);
	Com_Printf(CON_CHANNEL_SR_DEBUG, "-------- Backtrace Completed --------\n");
}

void Sys_SigHandler(int signal, struct sigcontext ctx)
{
	if (signal == SIGSEGV || signal == SIGTRAP || signal == SIGBUS || signal == SIGIOT || signal == SIGILL
		|| signal == SIGFPE)
	{
		Sys_DumpCrash(signal, &ctx);
	}
	Sys_DoSignalAction(signal, strsignal(signal));
}

/*
Sys_PlatformInit

Unix specific initialisation
*/
void Sys_PlatformInit(void)
{
	struct sigaction sa;
	sa.sa_handler = (void *)Sys_SigHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTRAP, &sa, NULL);
	sigaction(SIGIOT, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);

	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL); // No corefiles get generated with it
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	//  sigaction( SIGCHLD, &sa, NULL );
}

void Sys_TermProcess()
{
	while (waitpid(-1, 0, WNOHANG) > 0)
		;
}

char **GetStrTable(void *buff, int len, void *text)
{
	return NULL;
}

unsigned int Sys_GetProcessAffinityMask()
{
	unsigned int processAffinityMask;
	unsigned int cpucount = 0;
	unsigned int size = sizeof(cpucount);

	if (sysctlbyname("hw.ncpu", &cpucount, &size, 0, 0) || cpucount <= 1)
	{
		processAffinityMask = 1;
	}
	else
	{
		processAffinityMask = 3;
	}
	return processAffinityMask;
}

void Sys_SetThreadName(threadid_t tid, const char *name)
{
	pthread_t ti;
	if ((int)tid == -1)
	{
		ti = pthread_self();
	}
	else
	{
		ti = tid;
	}
	pthread_set_name_np(ti, name);
}

#endif
