#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <server.h>

void SR_Initialize();
void SR_Shutdown();
void SR_SpawnServer(const char *levelname);
void SR_Restart();
void SR_InitializePlayer(client_t *cl);
void SR_FreePlayer(client_t *cl);
void SR_InitializeEntity(gentity_t *ent);
void SR_SetMapAmbient(const char *alias, int volume);

void SR_Frame();
void SR_Packet(netadr_t *from, client_t* cl, msg_t *msg);
void SR_BroadcastVoice(gentity_t *talker, struct VoicePacket_t *packet);
void SR_ClientSpawn(gclient_t *client);
void SR_CalculateFrame(client_t *cl, usercmd_t *cmd);

void SR_Print(conChannel_t channel, char *msg);

void SR_DemoFrame(client_t *cl);
qboolean SR_DemoIsPlaying(client_t *cl);
void SR_DemoButton(client_t *cl, usercmd_t *cmd);
void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force);

float Pmove_GetJumpHeight(unsigned int num);
float Pmove_GetSpeedScale(playerState_t *ps);

#ifdef __cplusplus
}
#endif
