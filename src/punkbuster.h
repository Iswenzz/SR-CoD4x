#ifdef PUNKBUSTER

__cdecl int PbSvSendToAddrPort(char* netdest, unsigned short port, int msgsize, char* message);
__cdecl int PbSvSendToClient(int msgsize, char* message, int clientnum);
__cdecl char* PbSvGameQuery(int para_01, char* string);
qboolean PbServerInitialize(void);
void __cdecl PbServerProcessEvents(int type);
const char* __cdecl PbAuthClient(const char* NETAdrString, qboolean cl_punkbuster, const char* pbguid);
void __cdecl PbPassConnectString(const char* NETAdrString, const char* connectstring);
void __cdecl PbSvAddEvent(int event_type, int clientnum, int sizeofstring, char* string);
void __cdecl PbCaptureConsoleOutput(const char* msg, int size);
void __cdecl PbServerForceProcess();
void PbCaptureConsoleOutput_wrapper(const char* msg, int msglen);
void PbServerCompleteCommand(char* string, int len);
void DisablePbSv();
void EnablePbSv();
#endif
