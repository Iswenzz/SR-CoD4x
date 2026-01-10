#ifndef SEC_CRYPTO_H
#define SEC_CRYPTO_H

#include "q_shared.h"
#include "tomcrypt/tomcrypt.h"

extern int SEC_HASH_SHA1;
extern int SEC_HASH_SHA256;
extern int SEC_HASH_TIGER;

qboolean Sec_HashMemory(int algo, void *in, size_t inSize, void *out, long unsigned int *outSize,
	qboolean binaryOutput);
qboolean Sec_HashFile(int algo, const char *fname, void *out, long unsigned *outSize, qboolean binaryOutput);
qboolean Sec_BinaryToHex(char *in, unsigned long inSize, char *out, unsigned long *outSize);

#endif
