#include "Player.hpp"

namespace SR
{
	void PlayerCommands::Register()
	{
		Scr_AddMethod("surfaceflags", SurfaceFlags, qfalse);
		Scr_AddMethod("getviewheightlerpdown", GetViewHeightLerpDown, qfalse);
		Scr_AddMethod("getviewheightlerptarget", GetViewHeightLerpTarget, qfalse);
		Scr_AddMethod("getviewheightlerptime", GetViewHeightLerpTime, qfalse);
		Scr_AddMethod("getdamagetimer", GetDamageTimer, qfalse);
		Scr_AddMethod("weaponstate", GetWeaponState, qfalse);
		Scr_AddMethod("voicechatbuttonpressed", VoiceChatButtonPressed, qfalse);
		Scr_AddMethod("radioenable", RadioEnable, qfalse);
		Scr_AddMethod("proximityenable", ProximityEnable, qfalse);
	}

	void PlayerCommands::VoiceChatButtonPressed(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddBool(player->Voice);
	}

	void PlayerCommands::SurfaceFlags(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->SurfaceFlags);
	}

	void PlayerCommands::GetViewHeightLerpDown(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->ps->viewHeightLerpDown);
	}

	void PlayerCommands::GetViewHeightLerpTarget(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->ps->viewHeightLerpTarget);
	}

	void PlayerCommands::GetViewHeightLerpTime(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->ps->viewHeightLerpTime);
	}

	void PlayerCommands::GetDamageTimer(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->ps->damageTimer);
	}

	void PlayerCommands::GetWeaponState(scr_entref_t num)
	{
		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		Scr_AddInt(player->ps->weaponstate);
	}

	void PlayerCommands::RadioEnable(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: RadioEnable(<state>)");

		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		player->RadioEnabled = Scr_GetInt(0);
	}

	void PlayerCommands::ProximityEnable(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: ProximityEnable(<state>)");

		Ref<Player> player = Player::Get(num.entnum);

		if (!player)
		{
			Scr_ObjectError("Player not found.\n");
			return;
		}
		player->ProximityEnabled = Scr_GetInt(0);
	}
}
