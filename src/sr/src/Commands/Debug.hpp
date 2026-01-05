#pragma once
#include "Command.hpp"

namespace SR
{
	class DebugCommands
	{
	public:
		static void Register();
		static void Test();
		static void Entity();
		static void Breakpoint();
		static void ScriptUsage();
	};
}
