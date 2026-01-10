
//
// Name:         l_log.c
// Function:     log file stuff
// Programmer:   Mr Elusive (MrElusive@demigod.demon.nl)
// Last update:  1997-12-31
// Tab Size:     3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "qbsp.h"

#define MAX_LOGFILENAMESIZE 1024

typedef struct logfile_s
{
	char filename[MAX_LOGFILENAMESIZE];
	FILE *fp;
	int numwrites;
} logfile_t;

logfile_t logfile;

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_Open(char *filename)
{
	if (!filename || !strlen(filename))
	{
		printf("openlog <filename>\n");
		return;
	} // end if
	if (logfile.fp)
	{
		printf("log file %s is already opened\n", logfile.filename);
		return;
	} // end if
	logfile.fp = fopen(filename, "wb");
	if (!logfile.fp)
	{
		printf("can't open the log file %s\n", filename);
		return;
	} // end if
	strncpy(logfile.filename, filename, MAX_LOGFILENAMESIZE);
	printf("Opened log %s\n", logfile.filename);
} // end of the function Log_Create

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_Close(void)
{
	if (!logfile.fp)
	{
		printf("no log file to close\n");
		return;
	} // end if
	if (fclose(logfile.fp))
	{
		printf("can't close log file %s\n", logfile.filename);
		return;
	} // end if
	logfile.fp = NULL;
	printf("Closed log %s\n", logfile.filename);
} // end of the function Log_Close

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_Shutdown(void)
{
	if (logfile.fp)
	{
		Log_Close();
	}
} // end of the function Log_Shutdown

//
// Parameter:			-
// Returns:				-
// Changes Globals:		-

void Log_UnifyEndOfLine(char *buf)
{
	int i;

	for (i = 0; buf[i]; i++)
	{
		if (buf[i] == '\n')
		{
			if (i <= 0 || buf[i - 1] != '\r')
			{
				memmove(&buf[i + 1], &buf[i], strlen(&buf[i]) + 1);
				buf[i] = '\r';
				i++;
			} // end if
		} // end if
	} // end for
} // end of the function Log_UnifyEndOfLine

//
// Parameter:			-
// Returns:				-
// Changes Globals:		-

void Log_Print(char *fmt, ...)
{
	va_list ap;
	char buf[2048];

	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);

	if (verbose)
	{
#ifdef WINBSPC
		WinBSPCPrint(buf);
#else
		printf("%s", buf);
#endif // WINBSPS
	} // end if

	if (logfile.fp)
	{
		Log_UnifyEndOfLine(buf);
		fprintf(logfile.fp, "%s", buf);
		fflush(logfile.fp);
	} // end if
} // end of the function Log_Print

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_Write(char *fmt, ...)
{
	va_list ap;
	char buf[2048];

	if (!logfile.fp)
	{
		return;
	}
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);
	Log_UnifyEndOfLine(buf);
	fprintf(logfile.fp, "%s", buf);
	fflush(logfile.fp);
} // end of the function Log_Write

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_WriteTimeStamped(char *fmt, ...)
{
	va_list ap;

	if (!logfile.fp)
	{
		return;
	}
	/*	fprintf(logfile.fp, "%d   %02d:%02d:%02d:%02d   ",
						logfile.numwrites,
						(int) (botlibglobals.time / 60 / 60),
						(int) (botlibglobals.time / 60),
						(int) (botlibglobals.time),
						(int) ((int) (botlibglobals.time * 100)) -
								((int) botlibglobals.time) * 100);*/
	va_start(ap, fmt);
	vfprintf(logfile.fp, fmt, ap);
	va_end(ap);
	logfile.numwrites++;
	fflush(logfile.fp);
} // end of the function Log_Write

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

FILE *Log_FileStruct(void)
{
	return logfile.fp;
} // end of the function Log_FileStruct

//
// Parameter:				-
// Returns:					-
// Changes Globals:		-

void Log_Flush(void)
{
	if (logfile.fp)
	{
		fflush(logfile.fp);
	}
} // end of the function Log_Flush
