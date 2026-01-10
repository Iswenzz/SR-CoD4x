#ifndef __NET_GAME_H__
#define __NET_GAME_H__

#include "q_shared.h"
#include "sys_net.h"
#include "msg.h"

void NET_UDPPacketEvent(netadr_t* from, void* data, int len, int buflen);
unsigned int NET_TimeGetTime();

void NET_TCPConnectionClosed(netadr_t* adr, int connectionId, int serviceId);
tcpclientstate_t NET_TCPAuthPacketEvent(netadr_t* remote, byte* bufData, int cursize, int* connectionId,
	int* serviceId);
qboolean NET_TCPPacketEvent(netadr_t* remote, byte* bufData, int cursize, int* connectionId, int* serviceId);

void NET_TCPAddEventType(int (*tcpevent)(netadr_t* from, msg_t* msg, int connectionId),
	qboolean (*tcpserviceidentevent)(netadr_t* from, msg_t* msg, int* connectionId),
	void (*tcpconncloseevent)(netadr_t* from, int connectionId), int serviceId);

#endif
