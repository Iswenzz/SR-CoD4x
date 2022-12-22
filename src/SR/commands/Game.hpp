#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class GameCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Is asset precached.
		static void IsPrecached();

		/// @brief Play audio on the radio.
		static void RadioPlay();
	};
}
