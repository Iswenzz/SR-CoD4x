// #define Sec_Malloc(x) malloc(x)

void *Sec_Malloc(size_t size);
#define Sec_MemInit(n) void *_secmem[n]
#define Sec_GMalloc(type, n) (type *)Sec_Malloc(sizeof(type) * n)
#define Sec_SMalloc(n) Sec_GMalloc(char, n)

#define Sec_Free(x) \
	if (x != NULL)  \
		free(x);    \
	x = NULL

extern int SecCryptErr;
char *Sec_CryptErrStr(int);

void Sec_Init(void);
qboolean Sec_Initialized();
