#include "Log.hpp"

namespace SR
{
	void Log::Write(const std::string& msg)
	{
		Sys_Print(msg.c_str());
		Com_PrintLogfile(msg.c_str());
	}
}
