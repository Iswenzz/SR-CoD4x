
//
// Name:			l_bsp_ent.c
// Function:		bsp entity parsing
// Programmer:		Mr Elusive (MrElusive@demigod.demon.nl)
// Last update:		1999-04-05
// Tab Size:		3
// Notes:			-

#include "l_cmd.h"
#include "l_math.h"
#include "l_mem.h"
#include "l_log.h"
#include "../botlib/l_script.h"
#include "l_bsp_ent.h"

#define MAX_KEY 32
#define MAX_VALUE 1024

int num_entities;
entity_t entities[MAX_MAP_ENTITIES];

void StripTrailing(char *e)
{
	char *s;

	s = e + strlen(e) - 1;
	while (s >= e && *s <= 32)
	{
		*s = 0;
		s--;
	}
}

epair_t *ParseEpair(script_t *script)
{
	epair_t *e;
	token_t token;

	e = GetMemory(sizeof(epair_t));
	memset(e, 0, sizeof(epair_t));

	PS_ExpectAnyToken(script, &token);
	StripDoubleQuotes(token.string);
	if (strlen(token.string) >= MAX_KEY - 1)
	{
		Error("ParseEpair: token %s too long", token.string);
	}
	e->key = copystring(token.string);
	PS_ExpectAnyToken(script, &token);
	StripDoubleQuotes(token.string);
	if (strlen(token.string) >= MAX_VALUE - 1)
	{
		Error("ParseEpair: token %s too long", token.string);
	}
	e->value = copystring(token.string);

	// strip trailing spaces
	StripTrailing(e->key);
	StripTrailing(e->value);

	return e;
} // end of the function ParseEpair

qboolean ParseEntity(script_t *script)
{
	epair_t *e;
	entity_t *mapent;
	token_t token;

	if (!PS_ReadToken(script, &token))
	{
		return false;
	}

	if (strcmp(token.string, "{"))
	{
		Error("ParseEntity: { not found");
	}

	if (num_entities == MAX_MAP_ENTITIES)
	{
		Error("num_entities == MAX_MAP_ENTITIES");
	}

	mapent = &entities[num_entities];
	num_entities++;

	do
	{
		if (!PS_ReadToken(script, &token))
		{
			Error("ParseEntity: EOF without closing brace");
		}
		if (!strcmp(token.string, "}"))
		{
			break;
		}
		PS_UnreadLastToken(script);
		e = ParseEpair(script);
		e->next = mapent->epairs;
		mapent->epairs = e;
	} while (1);

	return true;
} // end of the function ParseEntity

void PrintEntity(entity_t *ent)
{
	epair_t *ep;

	printf("------- entity %p -------\n", ent);
	for (ep = ent->epairs; ep; ep = ep->next)
	{
		printf("%s = %s\n", ep->key, ep->value);
	}
}

void SetKeyValue(entity_t *ent, char *key, char *value)
{
	epair_t *ep;

	for (ep = ent->epairs; ep; ep = ep->next)
		if (!strcmp(ep->key, key))
		{
			FreeMemory(ep->value);
			ep->value = copystring(value);
			return;
		}
	ep = GetMemory(sizeof(*ep));
	ep->next = ent->epairs;
	ent->epairs = ep;
	ep->key = copystring(key);
	ep->value = copystring(value);
}

char *ValueForKey(entity_t *ent, char *key)
{
	epair_t *ep;

	for (ep = ent->epairs; ep; ep = ep->next)
		if (!strcmp(ep->key, key))
		{
			return ep->value;
		}
	return "";
}

vec_t FloatForKey(entity_t *ent, char *key)
{
	char *k;

	k = ValueForKey(ent, key);
	return atof(k);
}

void GetVectorForKey(entity_t *ent, char *key, vec3_t vec)
{
	char *k;
	double v1, v2, v3;

	k = ValueForKey(ent, key);
	// scanf into doubles, then assign, so it is vec_t size independent
	v1 = v2 = v3 = 0;
	sscanf(k, "%lf %lf %lf", &v1, &v2, &v3);
	vec[0] = v1;
	vec[1] = v2;
	vec[2] = v3;
}
