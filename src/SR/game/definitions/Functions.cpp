#include "Functions.hpp"
#include "SR.hpp"

C_EXTERN
{
	void SR_Initialize()
	{
		SR = new Game();
	}

	void SR_Shutdown()
	{
		delete SR;
	}

	void SR_InitializePlayer(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return;

		SR->Players[cl->gentity->s.number] = std::make_shared<Player>(cl);
	}

	void SR_FreePlayer(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return;

		SR->Players[cl->gentity->s.number]->Disconnect();
	}

	void SR_ClientSpawn(gclient_t *client)
	{
		if (!IsDefinedGClient(client))
			return;

		SR->Players[client->ps.clientNum]->Spawn();
	}

	void SR_CalculateFrame(client_t *cl, usercmd_t *cmd)
	{
		if (!IsDefinedClient(cl))
			return;

		int time = cmd->serverTime - cl->lastUsercmd.serverTime;
		SR->Players[cl->gentity->s.number]->CalculateFrame(time);
	}

	void SR_InitializeEntity(gentity_t *ent)
	{
		if (!ent) return;

		int num = ent->s.number;
		if (num < 0 || num >= MAX_GENTITIES)
			return;

		SR->Entities[num] = std::make_shared<Entity>(ent);
	}

	void SR_SetMapAmbient(const char *alias, int volume)
	{
		if (SR->Server->Map->AmbientStarted)
			return;

		SR->Server->Map->AmbientAlias = alias;
		SR->Server->Map->AmbientVolume = volume + 1000;
	}

	void SR_Frame()
	{
		SR->Server->Frame();
	}

	void SR_SpawnServer(const char *levelname)
	{
		SR->Server->Spawn(levelname);
	}

	void SR_Restart()
	{
		SR->Server->Restart();
	}

	void SR_BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		SR->Server->Voice->BroadcastVoice(talker, packet);
	}

	qboolean SR_DemoIsPlaying(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return qfalse;

		auto player = SR->Players[cl->gentity->client->ps.clientNum];
		return static_cast<qboolean>(player && !!player->DemoPlayer->Demo);
	}

	void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force)
	{
		auto player = SR->Players[cl->gentity->client->ps.clientNum];
		player->DemoPlayer->UpdateEntity(snapInfo, msg, time, from, to, force);
	}

	void SR_DemoButton(client_t *cl, usercmd_t *cmd)
	{
		if (!IsDefinedClient(cl))
			return;

		cl->gentity->client->ps.dofNearStart = *reinterpret_cast<float *>(&cmd->forwardmove);
		cl->gentity->client->ps.dofNearEnd = *reinterpret_cast<float *>(&cmd->rightmove);
		cl->gentity->client->ps.dofFarStart = *reinterpret_cast<float *>(&cmd->buttons);
	}

	void SR_DemoFrame(client_t *cl)
	{
		DemoRecord::Frame(cl);
	}

	void SR_Packet(netadr_t *from, client_t* cl, msg_t *msg)
	{
		SR->Netchan->Packet(from, cl, msg);
	}

	void SR_Print(conChannel_t channel, char *msg)
	{
		Log::Write(channel, msg);
	}

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

	void NetchanDebugSize(int size)
	{
		Debug::NetchanPacketSize(size);
	}

	qboolean VegasConnect(netadr_t *from, msg_t *msg, int *connectionId)
	{
		return static_cast<qboolean>(SR->Server->Vegas->Connect(from, msg));
	}

	void VegasDisconnect(netadr_t *from, int connectionId)
	{
		SR->Server->Vegas->Disconnect(from);
	}

	int VegasMessage(netadr_t *from, msg_t *msg, int connectionId)
	{
		return SR->Server->Vegas->Message(from, msg);
	}
}
