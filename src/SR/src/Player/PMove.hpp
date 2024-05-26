#pragma once
#include "Player.hpp"

namespace SR
{
	/// @brief Player movement.
	class PMove
	{
	public:
		Ref<class Player> Player;

		/// @brief Initialier a new PMove.
		/// @param player - The player.
		PMove(const Ref<class Player>& player);
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
		void JumpUpdateSurface(pml_t* pml);
	};
}
