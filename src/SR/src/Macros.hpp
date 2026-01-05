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

// clang-format off
#ifndef IZ_C
	#ifdef __cplusplus
		#define IZ_C extern "C"
		#define IZ_C_START IZ_C {
		#define IZ_C_END }
	#else
		#define IZ_C
		#define IZ_C_START
		#define IZ_C_END
	#endif
#endif

#ifndef IZ_CPP
	#ifdef __cplusplus
		#define IZ_CPP extern "C++"
		#define IZ_CPP_START IZ_CPP {
		#define IZ_CPP_END }
	#else
		#define IZ_CPP
		#define IZ_CPP_START
		#define IZ_CPP_END
	#endif
#endif
// clang-format on

#define CHECK_PARAMS(count, message) \
	if (Scr_GetNumParam() != count)  \
	{                                \
		Scr_Error(message);          \
		return;                      \
	}

#define DEFINED_GCLIENT(client) (client)

#define DEFINED_CLIENT(cl) (cl && cl->gentity && cl->gentity->client)
#define DEFINED_CLIENT_NUM(num) \
	(Player::List[num] && Player::List[num]->cl->gentity && Player::List[num]->cl->gentity->client)

#define DEFINED_ENTITY(ent) (ent && ent->s.number > 0 && ent->s.number < MAX_GENTITIES)
#define DEFINED_ENTITY_NUM(num) (Entity::List[num] && Entity::List[num]->g)
