#include <windows.h>

LPVOID __cdecl _VirtualAlloc(LPVOID address, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	return VirtualAlloc(address, dwSize, flAllocationType, flProtect);
}

BOOL __cdecl _VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
	return VirtualFree(lpAddress, dwSize, dwFreeType);
}

DWORD __cdecl _SleepEx(DWORD dwMilliseconds, BOOL bAlertable)
{
	return SleepEx(dwMilliseconds, bAlertable);
}

BOOL __cdecl _CloseHandle(HANDLE hObject)
{
	return CloseHandle(hObject);
}

DWORD __cdecl _GetLastError()
{
	return GetLastError();
}

void __cdecl _SetLastError(DWORD dwErrCode)
{
	return SetLastError(dwErrCode);
}

BOOL __cdecl _ReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped,
	LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	return ReadFileEx(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
}

HANDLE __cdecl _CreateFileA(char *lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile)
{
	return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes, hTemplateFile);
}

DWORD __cdecl _GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
{
	return GetFileSize(hFile, lpFileSizeHigh);
}

DWORD __cdecl _GetFileAttributesA(const char *lpFileName)
{
	return GetFileAttributesA(lpFileName);
}

BOOL __cdecl _SetFileAttributesA(const char *lpFileName, DWORD dwFileAttributes)
{
	return SetFileAttributesA(lpFileName, dwFileAttributes);
}
