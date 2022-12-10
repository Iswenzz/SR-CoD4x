#include "Player.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
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
	}

	void PlayerCommands::VoiceChatButtonPressed(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}

		auto player = SR->Players[num.entnum];
		Scr_AddBool(player->Voice);
	}

	void PlayerCommands::SurfaceFlags(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(SR->Players[ent->client->ps.clientNum]->SurfaceFlags);
	}

	void PlayerCommands::GetViewHeightLerpDown(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpDown);
	}

	void PlayerCommands::GetViewHeightLerpTarget(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpTarget);
	}

	void PlayerCommands::GetViewHeightLerpTime(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpTime);
	}

	void PlayerCommands::GetDamageTimer(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.damageTimer);
	}

	void PlayerCommands::GetWeaponState(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.weaponstate);
	}
}
