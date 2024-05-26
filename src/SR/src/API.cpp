#include "API.hpp"
#include "Application.hpp"

#include "Audio/Voice.hpp"
#include "Network/Netchan.hpp"
#include "Server/Map.hpp"
#include "Server/Server.hpp"
#include "System/Debug.hpp"

#include "Demo/DemoRecord.hpp"
#include "Entity/Entity.hpp"
#include "Player/Player.hpp"

IZ_C_START

void SR_Initialize()
{
	Application::Start();
}

void SR_Shutdown()
{
	Application::Shutdown();
}

void SR_InitializePlayer(client_t *cl)
{
	if (!DEFINED_CLIENT(cl))
		return;

	Player::Add(cl);
}

void SR_FreePlayer(client_t *cl)
{
	if (!DEFINED_CLIENT(cl))
		return;

	auto &player = Player::Get(cl->gentity->s.number);
	if (player)
		player->Disconnect();
}

void SR_ClientSpawn(gclient_t *client)
{
	if (!DEFINED_GCLIENT(client))
		return;

	Player::Get(client->ps.clientNum)->Spawn();
}

void SR_CalculateFrame(client_t *cl, usercmd_t *cmd)
{
	if (!DEFINED_CLIENT(cl))
		return;

	int time = cmd->serverTime - cl->lastUsercmd.serverTime;
	Player::Get(cl->gentity->s.number)->CalculateFrame(time);
}

void SR_InitializeEntity(gentity_t *ent)
{
	if (!DEFINED_ENTITY(ent))
		return;

	Entity::Add(ent);
}

void SR_SetMapAmbient(const char *alias, int volume)
{
	Map::SetAmbient(alias, volume);
}

void SR_Frame()
{
	Server::Frame();
}

void SR_SpawnServer(const char *levelname)
{
	Server::Spawn(levelname);
}

void SR_Restart()
{
	Server::Restart();
}

void SR_BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
{
	Voice::BroadcastVoice(talker, packet);
}

qboolean SR_DemoIsPlaying(client_t *cl)
{
	if (!DEFINED_CLIENT(cl))
		return qfalse;

	const auto &player = Player::Get(cl->gentity->client->ps.clientNum);
	return static_cast<qboolean>(player && !!player->DemoPlayer->Demo);
}

void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t *msg, const int time, entityState_t *from,
	entityState_t *to, qboolean force)
{
	const auto &player = Player::Get(cl->gentity->client->ps.clientNum);
	player->DemoPlayer->UpdateEntity(snapInfo, msg, time, from, to, force);
}

void SR_DemoButton(client_t *cl, usercmd_t *cmd)
{
	if (!DEFINED_CLIENT(cl))
		return;

	cl->gentity->client->ps.dofNearStart = *reinterpret_cast<float *>(&cmd->forwardmove);
	cl->gentity->client->ps.dofNearEnd = *reinterpret_cast<float *>(&cmd->rightmove);
	cl->gentity->client->ps.dofFarStart = *reinterpret_cast<float *>(&cmd->buttons);
}

void SR_DemoFrame(client_t *cl)
{
	DemoRecord::Frame(cl);
}

void SR_Packet(netadr_t *from, client_t *cl, msg_t *msg)
{
	Netchan::Packet(from, cl, msg);
}

void SR_Print(conChannel_t channel, char *msg)
{
	Log::Write(static_cast<Channel>(channel), msg);
}

int SR_PmoveGetSpeed(playerState_t *ps)
{
	return Player::Get(ps->clientNum)->PMove->GetSpeed();
}

float SR_PmoveGetSpeedScale(playerState_t *ps)
{
	return Player::Get(ps->clientNum)->PMove->GetSpeedScale();
}

int SR_PmoveGetGravity(playerState_t *ps)
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

IZ_C_END
