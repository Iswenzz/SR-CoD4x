#include "Voice.hpp"
#include "Speex.hpp"
#include "Audio.hpp"
#include "SR.hpp"

#define VOICE_AMPLIFY 2
#define PROXIMITY_DISTANCE 1500

namespace Iswenzz::CoD4x
{
	std::vector<short> Voice::Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity)
	{
		float distance = fabs(VectorDistance(talker->client->ps.origin, entity->client->ps.origin));

		if (distance > PROXIMITY_DISTANCE)
			distance = PROXIMITY_DISTANCE;
		distance = 1 - (distance / PROXIMITY_DISTANCE);
		distance *= VOICE_AMPLIFY;

		return Audio::Amplify(data, distance);
	}

	void Voice::BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		int i;
		gentity_t* entity;

		std::vector<short> voiceData = Speex::Decode(packet);
		talker->client->lastVoiceTime = level.time;

		for (i = 0, entity = level.gentities; i < level.maxclients; i++, entity++)
		{
			if (entity->client && entity->client->sess.sessionState != SESS_STATE_INTERMISSION)
			{
				if (!voice_localEcho->boolean && entity == talker)
					continue;
				if (!voice_global->boolean && !OnSameTeam(entity, talker))
					continue;
				if (!voice_deadChat->boolean && entity->client->sess.sessionState == SESS_STATE_DEAD)
					continue;

				std::vector<short> proximityData = Proximity(voiceData, talker, entity);
				VoicePacket_t newPacket = Speex::Encode(proximityData);
				newPacket.talker = packet->talker;

				if (!SV_ClientHasClientMuted(i, talker->s.number) && SV_ClientWantsVoiceData(i))
					SV_QueueVoicePacket(talker->s.number, i, &newPacket);
			}
		}
	}
}

C_EXTERN
{
	void SR_BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		SR->Server->Voice->BroadcastVoice(talker, packet);
	}
}
