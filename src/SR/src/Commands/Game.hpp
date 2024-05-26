#pragma once
#include "Command.hpp"

namespace SR
{
	class GameCommands
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Is asset precached.
		static void IsPrecached();

		/// @brief Get the current name of a legacy weapon.
		static void LegacyWeapon();

		/// @brief Play audio on the radio.
		static void RadioPlay();
	};
}
