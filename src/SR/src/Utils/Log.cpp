#include "Log.hpp"

#include "Base.hpp"

#include <stdarg.h>

namespace SR
{
	void Log::Write(Channel channel, const std::string& msg)
	{
		Log::Write(msg);
	}

	void Log::Write(const std::string& fmt, ...)
	{
		va_list argptr;
		char msg[4096];

		const char* cfmt = fmt.c_str();

		va_start(argptr, cfmt);
		Q_vsnprintf(msg, sizeof(msg), cfmt, argptr);
		va_end(argptr);

		Sys_Print(msg);
		Com_PrintLogfile(msg);
	}

	void Log::WriteLine(const std::string& fmt, ...)
	{
		va_list argptr;
		char msg[4096];

		const char* cfmt = fmt.c_str();

		va_start(argptr, cfmt);
		Q_vsnprintf(msg, sizeof(msg), cfmt, argptr);
		va_end(argptr);

		strcat(msg, "\n\0");

		Sys_Print(msg);
		Com_PrintLogfile(msg);
	}
}
