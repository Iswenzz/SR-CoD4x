#pragma once
#include "Command.hpp"

namespace SR
{
	class DebugCommands
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Debug test.
		static void Test();

		/// @brief Debug entity.
		static void Entity();

		/// @brief Debug breakpoint.
		static void Breakpoint();

		/// @brief Get the variables script usage.
		static void ScriptUsage();
	};
}
