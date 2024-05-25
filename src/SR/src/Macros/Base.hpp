#pragma once

#ifndef CDECL
	#define CDECL __cdecl
#endif

#ifndef OPTIMIZE3
	#define OPTIMIZE3 __optimize3
#endif

#ifndef STDCALL
	#define STDCALL __stdcall
#endif

#ifndef IZ_C
	#ifdef __cplusplus
		#define IZ_C extern "C"
	#else
		#define IZ_C
	#endif
#endif

#ifndef IZ_CPP
	#ifdef __cplusplus
		#define IZ_CPP extern "C++"
	#else
		#define IZ_CPP
	#endif
#endif

#define CHECK_PARAMS(count, message) \
	if (Scr_GetNumParam() != count)  \
	{                                \
		Scr_Error(message);          \
		return;                      \
	}
