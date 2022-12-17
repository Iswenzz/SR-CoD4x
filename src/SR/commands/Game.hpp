#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class GameCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Play audio on the radio.
		static void RadioPlay();

		/// @brief Enable radio for a player.
		static void RadioEnable(scr_entref_t num);

		/// @brief Enable proximity for a player.
		static void ProximityEnable(scr_entref_t num);
	};
}
