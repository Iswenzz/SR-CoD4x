#include "Debug.hpp"

#include <signal.h>
#ifdef _WIN32
	#include <debugapi.h>
#endif

namespace Iswenzz::CoD4x
{
	void DebugCommands::Register()
	{
		Scr_AddFunction("debug_test", Test, qfalse);
		Scr_AddFunction("debug_entity", Entity, qfalse);
		Scr_AddFunction("debug_breakpoint", Breakpoint, qfalse);
		Scr_AddFunction("debug_scriptusage", ScriptUsage, qfalse);
	}

	void DebugCommands::Test()
	{
		CHECK_PARAMS(0, "Usage: debug_test()");
	}

	void DebugCommands::Entity()
	{
		CHECK_PARAMS(1, "Usage: debug_entity(<entity>)");

		gentity_t *ent = Scr_GetEntity(0);

		Scr_AddString(G_GetEntityTypeName(ent));
	}

	void DebugCommands::Breakpoint()
	{
		CHECK_PARAMS(0, "Usage: debug_breakpoint()");

#ifdef _WIN32
		DebugBreak();
#else
		raise(SIGINT);
#endif
	}

	void DebugCommands::ScriptUsage()
	{
		CHECK_PARAMS(0, "Usage: debug_scriptusage()");

		Scr_AddInt(gScrVarPub.numScriptObjects + gScrVarPub.numScriptValues);
	}
}
