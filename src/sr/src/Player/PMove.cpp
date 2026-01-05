#include "PMove.hpp"

#include "Player.hpp"

namespace SR
{
	PMove::PMove(const Ref<class Player>& player)
	{
		Player = player;
	}

	void PMove::Initialize()
	{
		Player->ps->speed = g_speed->integer;
		Player->ps->gravity = static_cast<int>(g_gravity->value);
		Player->cl->jumpHeight = jump_height->value;
	}

	int PMove::GetSpeed()
	{
		return Player->ps->speed;
	}

	float PMove::GetSpeedScale()
	{
		return Player->ps->moveSpeedScaleMultiplier;
	}

	int PMove::GetGravity()
	{
		return Player->ps->gravity;
	}

	float PMove::GetJumpHeight()
	{
		return Player->cl->jumpHeight;
	}

	void PMove::JumpUpdateSurface(pml_t* pml)
	{
		Player->SurfaceFlags = pml->groundTrace.sflags;
	}
}
