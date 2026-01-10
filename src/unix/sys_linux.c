#include "../q_shared.h"
#include "../q_platform.h"

#ifndef __BSD__

	#include "../qcommon_mem.h"
	#include "../qcommon_io.h"
	#include "../qcommon.h"
	#include "../sys_main.h"
	#include "../cmd.h"
	#include "../sys_cod4defs.h"
	#include "../sec_crypto.h"
	#include "../objfile_parser.h"

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
	#include <wait.h>
	#include <sched.h>
	#include <pthread.h>

char** ELF32_GetStrTable(void* buff, int len, sharedlib_data_t* text);

static char homePath[MAX_OSPATH];

const char* Sys_DefaultHomePath(void)
{
	char* p;

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

const char* Sys_TempPath(void)
{
	const char* TMPDIR = getenv("TMPDIR");

	if (TMPDIR == NULL || TMPDIR[0] == '\0')
		return "/tmp";
	else
		return TMPDIR;
}

void Sys_PrintBacktrace(void* ctx)
{
	int numFrames;
	int i;
	void** traces;
	char** symbols;

	Com_Printf(CON_CHANNEL_SR_DEBUG, "---------- Backtrace ----------\n");
	traces = malloc(65536 * sizeof(void*));
	numFrames = backtrace(traces, 65536);
	symbols = backtrace_symbols(traces, numFrames);
	for (i = 0; i < numFrames; i++)
	{
		Com_Printf(CON_CHANNEL_SR_DEBUG, "%5d: %s\n", numFrames - i - 1, symbols[i]);
	}
	free(traces);
}

void Sys_DumpCrash(int signal, struct sigcontext* ctx)
{
	char hash[65];
	long unsigned size = sizeof(hash);

	Com_Printf(CON_CHANNEL_SR_DEBUG, "This program has crashed with signal: %s\n", strsignal(signal));
	Com_Printf(CON_CHANNEL_SR_DEBUG, "The current Gameversion is: %s %s %s type '%c' build %i %s\n", GAME_STRING,
		Q3_VERSION, PLATFORM_STRING, 'e', Sys_GetBuild(), __DATE__);
	Sec_HashFile(SEC_HASH_SHA256, Sys_ExeFile(), hash, &size, qfalse);
	// Q_strncpyz(hash, "File Hashing has not been implemented yet", sizeof(hash));
	hash[64] = '\0';
	Com_Printf(CON_CHANNEL_SR_DEBUG, "File is %s Hash is: %s\n", Sys_ExeFile(), hash);
	Sys_PrintBacktrace(NULL);
	Com_Printf(CON_CHANNEL_SR_DEBUG, "\n-- Registers ---\n");
	Com_Printf(CON_CHANNEL_SR_DEBUG,
		"edi 0x%lx\nesi 0x%lx\nebp 0x%lx\nesp 0x%lx\neax 0x%lx\nebx 0x%lx\necx 0x%lx\nedx 0x%lx\neip 0x%lx\n", ctx->edi,
		ctx->esi, ctx->ebp, ctx->esp, ctx->eax, ctx->ebx, ctx->ecx, ctx->edx, ctx->eip);
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
	sa.sa_handler = (void*)Sys_SigHandler;
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

char** GetStrTable(void* buff, int len, sharedlib_data_t* text)
{
	return ELF32_GetStrTable(buff, len, text);
}

unsigned int Sys_GetProcessAffinityMask()
{
	unsigned int AffinityMask = 0;
	cpu_set_t set;
	int i;

	sched_getaffinity(0, sizeof(set), &set);

	for (i = 0; i < 32; ++i)
	{
		if (CPU_ISSET(i, &set))
		{
			AffinityMask |= (1 << i);
		}
	}

	return AffinityMask;
}

void Sys_SetThreadName(threadid_t tid, const char* name)
{
	pthread_t ti;
	if (tid == -1)
	{
		ti = pthread_self();
	}
	else
	{
		ti = tid;
	}
	pthread_setname_np(ti, name);
}

#endif
