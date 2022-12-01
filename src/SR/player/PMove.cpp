#include "PMove.hpp"
#include "Player.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	PMove::PMove(class Player *Player)
	{
		this->Player = Player;
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

	void PMove::JumpUpdateSurface(pml_t *pml)
	{
		Player->SurfaceFlags = pml->groundTrace.sflags;
	}

	void PMove::StuckInClient() { }
}

C_EXTERN
{
	OPTIMIZE3 int Pmove_GetSpeed(playerState_t *ps)
	{
		return SR->Players[ps->clientNum]->PMove->GetSpeed();
	}

	float Pmove_GetSpeedScale(playerState_t *ps)
	{
		return SR->Players[ps->clientNum]->PMove->GetSpeedScale();
	}

	OPTIMIZE3 int Pmove_GetGravity(playerState_t *ps)
	{
		return SR->Players[ps->clientNum]->PMove->GetGravity();
	}

	float Pmove_GetJumpHeight(unsigned int num)
	{
		return SR->Players[num]->PMove->GetJumpHeight();
	}

	void Jump_UpdateSurface(playerState_s *ps, pml_t *pml)
	{
		SR->Players[ps->clientNum]->PMove->JumpUpdateSurface(pml);
	}

	OPTIMIZE3 void StuckInClient(gentity_t* gen) { }
}
