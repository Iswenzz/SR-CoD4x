#include "Netchan.hpp"
#include "SR.hpp"

C_EXTERN
{
	#include <huffman.h>
}

namespace Iswenzz::CoD4x
{
	void Netchan::Packet(netadr_t *from, client_t* cl, msg_t *msg)
	{
		if (!cl || !cl->gentity)
			return;

		auto player = SR->Players[cl->gentity->client->ps.clientNum];
		if (player)
			player->Packet(msg);
	}

	void Netchan::BroadcastVoice(struct gentity_s *entity, VoicePacket_t *packet)
	{
		int i;
		struct gentity_s* ent;

		entity->client->lastVoiceTime = level.time;

		for (i = 0, ent = level.gentities; i < level.maxclients; i++, ent++)
		{
			if (ent->r.broadcastTime != 0 && ent->client && ent->client->sess.sessionState != SESS_STATE_INTERMISSION)
			{
				// if (ent == entity)
				// 	continue;

				if (!SV_ClientHasClientMuted(i, entity->s.number) && SV_ClientWantsVoiceData(i))
					SV_QueueVoicePacket(entity->s.number, i, packet);
			}
		}
	}
}

C_EXTERN
{
	void SR_Packet(netadr_t *from, client_t* cl, msg_t *msg)
	{
		SR->Netchan->Packet(from, cl, msg);
	}

	void SR_BroadcastVoice(struct gentity_s *entity, VoicePacket_t *packet)
	{
		SR->Netchan->BroadcastVoice(entity, packet);
	}
}
