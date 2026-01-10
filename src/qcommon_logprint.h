#ifndef __QCOMMON_LOGPRINT_H__
#define __QCOMMON_LOGPRINT_H__

#include "q_shared.h"

#ifdef __cplusplus
extern "C"
{
#endif

	void QDECL SV_EnterLeaveLog(const char *fmt, ...);
	void QDECL Com_PrintAdministrativeLog(const char *msg);
	void Com_PrintLogfile(const char *msg);
	void Com_CloseLogFiles(void);
	fileHandle_t Com_OpenGameLogfile(const char *name, char mode, qboolean sync);
	void Com_CloseGameLogfile();
	int Com_WriteGameLogfile(const char *data, int len);

#ifdef __cplusplus
};
#endif

#endif
