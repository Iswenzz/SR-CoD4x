
//
// Name:         l_log.h
// Function:     log file stuff
// Programmer:   Mr Elusive (MrElusive@demigod.demon.nl)
// Last update:  1997-12-31
// Tab Size:     3

// open a log file
void Log_Open(char *filename);
// close the current log file
void Log_Close(void);
// close log file if present
void Log_Shutdown(void);
// print on stdout and write to the current opened log file
void Log_Print(char *fmt, ...);
// write to the current opened log file
void Log_Write(char *fmt, ...);
// write to the current opened log file with a time stamp
void Log_WriteTimeStamped(char *fmt, ...);
// returns the log file structure
FILE *Log_FileStruct(void);
// flush log file
void Log_Flush(void);

#ifdef WINBSPC
void WinBSPCPrint(char *str);
#endif // WINBSPC
