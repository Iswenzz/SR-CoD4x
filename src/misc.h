#ifndef __MISC_H__
#define __MISC_H__

#include "q_shared.h"
#include "player.h"

#ifdef __cplusplus
extern "C"
{
#endif
	void __cdecl Swap_Init(void);
	void __cdecl CSS_InitConstantConfigStrings(void);
	void __cdecl Con_InitChannels(void);
	void __cdecl SEH_UpdateLanguageInfo(void);
	void __cdecl SetAnimCheck(int);
	qboolean __cdecl BG_IsWeaponValid(playerState_t *ps, unsigned int index);
	qboolean __cdecl SEH_StringEd_GetString(const char *input);

	void AddRedirectLocations(void);
	qboolean __cdecl Com_LoadDvarsFromBuffer(const char **inputbuf, unsigned int length, const char *data_p,
		const char *filename);

#ifdef __cplusplus
}
#endif

#endif
