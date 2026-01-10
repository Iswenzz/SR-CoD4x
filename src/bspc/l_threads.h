extern int numthreads;

void ThreadSetDefault(void);
int GetThreadWork(void);
void RunThreadsOnIndividual(int workcnt, qboolean showpacifier, void (*func)(int));
void RunThreadsOn(int workcnt, qboolean showpacifier, void (*func)(int));

// mutex
void ThreadSetupLock(void);
void ThreadShutdownLock(void);
void ThreadLock(void);
void ThreadUnlock(void);
// semaphore
void ThreadSetupSemaphore(void);
void ThreadShutdownSemaphore(void);
void ThreadSemaphoreWait(void);
void ThreadSemaphoreIncrease(int count);
// add/remove threads
void AddThread(void (*func)(int));
void RemoveThread(int threadid);
void WaitForAllThreadsFinished(void);
int GetNumThreads(void);
