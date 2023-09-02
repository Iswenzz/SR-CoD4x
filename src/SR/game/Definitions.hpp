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

#ifndef C_EXTERN
	#ifdef __cplusplus
		#define C_EXTERN extern "C"
		#define C_EXTERN_START C_EXTERN {
		#define C_EXTERN_END }
	#else
		#define C_EXTERN
		#define C_EXTERN_START
		#define C_EXTERN_END
	#endif
#endif
#ifndef CPP_EXTERN
	#ifdef __cplusplus
		#define CPP_EXTERN extern "C++"
		#define CPP_EXTERN_START CPP_EXTERN {
		#define CPP_EXTERN_END }
	#else
		#define CPP_EXTERN
		#define CPP_EXTERN_START
		#define CPP_EXTERN_END
	#endif
#endif

#define CHECK_PARAMS(count, message) \
	if (Scr_GetNumParam() != count)  \
	{                                \
		Scr_Error(message);          \
		return;                      \
	}

#include "definitions/Functions.hpp"
