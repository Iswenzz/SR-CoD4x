#pragma once
#include "Player.hpp"

namespace SR
{
	class PMove
	{
	public:
		Ref<class Player> Player;

		PMove(const Ref<class Player>& player);
		virtual ~PMove() = default;

		void Initialize();
		int GetSpeed();
		float GetSpeedScale();
		int GetGravity();
		float GetJumpHeight();
		void JumpUpdateSurface(pml_t* pml);
	};
}
