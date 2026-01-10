
// memory.h
// #define MEMDEBUG
#undef MEMDEBUG

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef MEMDEBUG

	void *GetClearedMemory(int size);
	void *GetMemory(unsigned long size);

#else

	#define GetMemory(size) GetMemoryDebug(size, #size, __FILE__, __LINE__);
	#define GetClearedMemory(size) GetClearedMemoryDebug(size, #size, __FILE__, __LINE__);
// allocate a memory block of the given size
void *GetMemoryDebug(unsigned long size, char *label, char *file, int line);
// allocate a memory block of the given size and clear it
void *GetClearedMemoryDebug(unsigned long size, char *label, char *file, int line);
//
void PrintMemoryLabels(void);
#endif // MEMDEBUG

	void FreeMemory(void *ptr);
	int MemorySize(void *ptr);
	void PrintMemorySize(unsigned long size);
	int TotalAllocatedMemory(void);
	void *Hunk_Alloc(int size);

#ifdef __cplusplus
};
#endif
