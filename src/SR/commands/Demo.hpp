#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class DemoCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Register a speedrun demo.
		static void RegisterSpeedrunDemo();

		/// @brief Play a demo on a client.
		static void PlayDemo(scr_entref_t num);

		/// @brief Check if the demo is loading.
		static void IsDemoLoading();

		/// @brief Check if a demo is playing on a client.
		static void IsDemoPlaying(scr_entref_t num);

		/// @brief Get the speedrun velocity.
		static void GetSpeedrunVelocity(scr_entref_t num);

		/// @brief Get the demo timer.
		static void GetDemoTimer(scr_entref_t num);

		/// @brief Get the demo weapon.
		static void GetDemoWeapon(scr_entref_t num);

		/// @brief Get the demo right move.
		static void GetDemoRightMove(scr_entref_t num);

		/// @brief Get the demo forward move.
		static void GetDemoForwardMove(scr_entref_t num);

		/// @brief Get the demo buttons.
		static void GetDemoButtons(scr_entref_t num);

		/// @brief Stop a demo on a client.
		static void StopDemo(scr_entref_t num);
	};
}
