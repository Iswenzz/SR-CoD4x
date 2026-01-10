#include "plugin_crypto.h"

qboolean PHandler_Hash(pluginHash_t algo, void *in, size_t inSize, void *out, size_t outSize)
{
	if (in == NULL || out == NULL || inSize < 1 || outSize < (1))
	{
		return qfalse;
	}
	hash_state md;
	struct ltc_hash_descriptor *hs;
	switch (algo)
	{
	case P_HASH_SHA1:
		hs = (struct ltc_hash_descriptor *)&sha1_desc;
		break;
	case P_HASH_SHA256:
		hs = (struct ltc_hash_descriptor *)&sha256_desc;
		break;
	case P_HASH_TIGER:
		hs = (struct ltc_hash_descriptor *)&tiger_desc;
		break;
	default:
		return qfalse;
	}
	if (hs->hashsize >= outSize)
	{
		return qfalse;
	}
	hs->init(&md);
	hs->process(&md, in, inSize);
	hs->done(&md, out);
	return qtrue;
}
