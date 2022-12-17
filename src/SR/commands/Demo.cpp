#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void DemoCommands::Register()
	{
		Scr_AddMethod("playdemo", PlayDemo, qfalse);
		Scr_AddMethod("isdemoplaying", IsDemoPlaying, qfalse);
		Scr_AddMethod("getspeedrunvelocity", GetSpeedrunVelocity, qfalse);
		Scr_AddMethod("getdemoweapon", GetDemoWeapon, qfalse);
		Scr_AddMethod("getdemorightmove", GetDemoRightMove, qfalse);
		Scr_AddMethod("getdemoforwardmove", GetDemoForwardMove, qfalse);
		Scr_AddMethod("getdemobuttons", GetDemoButtons, qfalse);
		Scr_AddMethod("getdemotimer", GetDemoTimer, qfalse);
		Scr_AddMethod("stopdemo", StopDemo, qfalse);

		Scr_AddFunction("registerspeedrundemo", RegisterSpeedrunDemo, qfalse);
		Scr_AddFunction("isdemoloaded", IsDemoLoaded, qfalse);
	}

	void DemoCommands::RegisterSpeedrunDemo()
	{
		CHECK_PARAMS(5, "Usage: RegisterSpeedrunDemo(<map>, <playerId>, <runId>, <mode>, <way>)");

		std::string map = Scr_GetString(0);
		std::string playerId = Scr_GetString(1);
		std::string runId = Scr_GetString(2);
		std::string mode = Scr_GetString(3);
		std::string way = Scr_GetString(4);

		Scr_AddBool(SR->DemoContainer->RegisterSpeedrunDemo(map, playerId, runId, mode, way));
	}

	void DemoCommands::PlayDemo(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: PlayDemo(<id>)");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		std::string id = Scr_GetString(0);

		auto player = SR->Players[num.entnum];
		auto demo = SR->DemoContainer->Demos.find(id);

		if (demo != std::end(SR->DemoContainer->Demos))
		{
			player->DemoPlayer->Play(demo->second);
			Scr_AddEntity(player->DemoPlayer->Entity);
		}
	}

	void DemoCommands::IsDemoLoaded()
	{
		CHECK_PARAMS(1, "Usage: IsDemoLoaded(<id>)");

		std::string id = Scr_GetString(0);

		auto demo = SR->DemoContainer->Demos.find(id);
		if (demo != std::end(SR->DemoContainer->Demos))
			Scr_AddBool(demo->second->IsLoaded);
		else
			Scr_AddBool(qfalse);
	}

	void DemoCommands::IsDemoPlaying(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: IsDemoPlaying()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];
		Scr_AddBool(!!player->DemoPlayer->Demo);
	}

	void DemoCommands::GetSpeedrunVelocity(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetSpeedrunVelocity()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Velocity);
	}

	void DemoCommands::GetDemoWeapon(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: StopDemo()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];
		auto weapon = player->DemoPlayer->Weapon;

		Scr_AddString(weapon.c_str());
	}

	void DemoCommands::GetDemoRightMove(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetDemoRightMove()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Demo ? player->DemoPlayer->CurrentFrame.rightmove : 0);
	}

	void DemoCommands::GetDemoForwardMove(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetDemoForwardMove()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Demo ? player->DemoPlayer->CurrentFrame.forwardmove : 0);
	}

	void DemoCommands::GetDemoTimer(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetDemoTimer()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Demo ? player->DemoPlayer->CurrentFrame.time : 0);
	}

	void DemoCommands::GetDemoButtons(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetDemoButtons()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Demo ? player->DemoPlayer->CurrentFrame.buttons : 0);
	}

	void DemoCommands::StopDemo(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: StopDemo()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		player->DemoPlayer->Stop();
	}
}
