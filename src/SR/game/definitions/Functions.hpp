#pragma once
#include <server.h>

C_EXTERN_START

void SR_Initialize();
void SR_Shutdown();
void SR_SpawnServer(const char *levelname);
void SR_Restart();
void SR_InitializePlayer(client_t *cl);
void SR_FreePlayer(client_t *cl);
void SR_InitializeEntity(gentity_t *ent);
void SR_SetMapAmbient(const char *alias, int volume);

void SR_Frame();
void SR_Packet(netadr_t *from, client_t *cl, msg_t *msg);
void SR_BroadcastVoice(gentity_t *talker, struct VoicePacket_t *packet);
void SR_ClientSpawn(gclient_t *client);
void SR_CalculateFrame(client_t *cl, usercmd_t *cmd);

void SR_Print(conChannel_t channel, char *msg);
char *fmt(char *format, ...);

void SR_DemoFrame(client_t *cl);
qboolean SR_DemoIsPlaying(client_t *cl);
void SR_DemoButton(client_t *cl, usercmd_t *cmd);
void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t *msg, const int time, entityState_t *from, entityState_t *to, qboolean force);

float Pmove_GetJumpHeight(unsigned int num);
float Pmove_GetSpeedScale(playerState_t *ps);

qboolean VegasConnect(netadr_t *from, msg_t *msg, int *connectionId);
void VegasDisconnect(netadr_t *from, int connectionId);
int VegasMessage(netadr_t *from, msg_t *msg, int connectionId);

C_EXTERN_END
