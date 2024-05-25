#pragma once
#include "Macros/Base.hpp"

#include <bg_public.h>
#include <server.h>

IZ_C_START

void SR_Initialize();
void SR_Shutdown();
void SR_SpawnServer(const char *levelname);
void SR_Restart();
void SR_Frame();
void SR_Packet(netadr_t *from, client_t *cl, msg_t *msg);

void SR_InitializePlayer(client_t *cl);
void SR_FreePlayer(client_t *cl);
void SR_InitializeEntity(gentity_t *ent);
void SR_ClientSpawn(gclient_t *client);
void SR_CalculateFrame(client_t *cl, usercmd_t *cmd);
void SR_BroadcastVoice(gentity_t *talker, struct VoicePacket_t *packet);

void SR_NetchanDebugSize(int size);
void SR_SetMapAmbient(const char *alias, int volume);
void SR_Print(conChannel_t channel, char *msg);

void SR_DemoFrame(client_t *cl);
qboolean SR_DemoIsPlaying(client_t *cl);
void SR_DemoButton(client_t *cl, usercmd_t *cmd);
void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t *msg, const int time, entityState_t *from,
	entityState_t *to, qboolean force);

int SR_PmoveGetSpeed(playerState_t *ps);
float SR_PmoveGetSpeedScale(playerState_t *ps);
int SR_PmoveGetGravity(playerState_t *ps);
float SR_PmoveGetJumpHeight(unsigned int num);
void SR_JumpUpdateSurface(playerState_t *ps, struct pml_t *pml);

qboolean SR_VegasConnect(netadr_t *from, msg_t *msg, int *connectionId);
void SR_VegasDisconnect(netadr_t *from, int connectionId);
int SR_VegasMessage(netadr_t *from, msg_t *msg, int connectionId);

IZ_C_END
