#pragma once
#include "Player.hpp"
#include <memory>

C_EXTERN
{
	#include <g_shared.h>
	#include <g_sv_shared.h>
	#include <bg_public.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Player movement.
	class PMove
	{
	public:
		std::shared_ptr<class Player> Player;

		/// @brief Initialier a new PMove.
		/// @param player - The player.
		PMove(std::shared_ptr<class Player> player);
		virtual ~PMove() = default;

		/// @brief Initialize the player movement.
		void Initialize();

		/// @brief Get the player speed.
		int GetSpeed();

		/// @brief Get the player speed scale.
		float GetSpeedScale();

		/// @brief Get the player gravity.
		int GetGravity();

		/// @brief Get the player jump height.
		float GetJumpHeight();

		/// @brief Update the player surface type on jump.
		/// @param pml - The player movement.
		void JumpUpdateSurface(pml_t *pml);
	};
}
