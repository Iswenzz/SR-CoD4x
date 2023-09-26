#include "Server.hpp"
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

		Player::Add(cl);
	}

	void SR_FreePlayer(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return;

		auto player = Player::Get(cl->gentity->s.number);
		if (player)
			player->Disconnect();
	}

	void SR_ClientSpawn(gclient_t *client)
	{
		if (!IsDefinedGClient(client))
			return;

		Player::Get(client->ps.clientNum)->Spawn();
	}

	void SR_CalculateFrame(client_t *cl, usercmd_t *cmd)
	{
		if (!IsDefinedClient(cl))
			return;

		int time = cmd->serverTime - cl->lastUsercmd.serverTime;
		Player::Get(cl->gentity->s.number)->CalculateFrame(time);
	}

	void SR_InitializeEntity(gentity_t *ent)
	{
		if (!IsDefinedEntity(ent))
			return;

		Entity::Add(ent);
	}

	void SR_SetMapAmbient(const char *alias, int volume)
	{
		SR->Server->Map->SetAmbient(alias, volume);
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

		auto player = Player::Get(cl->gentity->client->ps.clientNum);
		return static_cast<qboolean>(player && !!player->DemoPlayer->Demo);
	}

	void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force)
	{
		auto player = Player::Get(cl->gentity->client->ps.clientNum);
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

	OPTIMIZE3 int SR_PmoveGetSpeed(playerState_t *ps)
	{
		return Player::Get(ps->clientNum)->PMove->GetSpeed();
	}

	float SR_PmoveGetSpeedScale(playerState_t *ps)
	{
		return Player::Get(ps->clientNum)->PMove->GetSpeedScale();
	}

	OPTIMIZE3 int SR_PmoveGetGravity(playerState_t *ps)
	{
		return Player::Get(ps->clientNum)->PMove->GetGravity();
	}

	float SR_PmoveGetJumpHeight(unsigned int num)
	{
		return Player::Get(num)->PMove->GetJumpHeight();
	}

	void SR_JumpUpdateSurface(playerState_s *ps, pml_t *pml)
	{
		Player::Get(ps->clientNum)->PMove->JumpUpdateSurface(pml);
	}

	void SR_NetchanDebugSize(int size)
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
