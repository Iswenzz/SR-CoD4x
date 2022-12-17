#include "Voice.hpp"
#include "Streamable.hpp"
#include "SR.hpp"

#define VOICE_AMPLIFY 2
#define PROXIMITY_DISTANCE 1500

namespace Iswenzz::CoD4x
{
	void Voice::Stream()
	{
		if (!Radio || !Radio->IsLoaded || Radio->IsStreamEnd()) return;

		int i;
		gentity_t* entity;
		client_t *cl;
		VoicePacket_t packet = { 0 };

		// Most spastic sound sync
		int iteration = 2;
		if (RadioFragments++ > 4)
		{
			iteration = 6;
			RadioFragments = 0;
		}

		for (int p = 0; p < iteration; p++)
		{
			packet = Radio->Play();

			for (i = 0, cl = svs.clients; i < level.maxclients; i++, cl++)
			{
				entity = &level.gentities[i];

				if (cl && cl->state == CS_ACTIVE && entity->client
					&& entity->client->sess.sessionState != SESS_STATE_INTERMISSION)
				{
					packet.talker = i;
					SV_QueueVoicePacket(i, i, &packet);
				}
			}
			if (Radio->IsStreamEnd())
				break;
		}
	}

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
		client_t *cl;

		std::vector<short> voiceData = Speex::Decode(packet);
		talker->client->lastVoiceTime = level.time;

		for (i = 0, cl = svs.clients; i < level.maxclients; i++, cl++)
		{
			entity = &level.gentities[i];

			if (cl && cl->state == CS_ACTIVE && entity->client
				&& entity->client->sess.sessionState != SESS_STATE_INTERMISSION)
			{
				if (!voice_localEcho->boolean && entity == talker)
					continue;
				if (!voice_global->boolean && !OnSameTeam(entity, talker))
					continue;

				if (entity->client->sess.sessionState == SESS_STATE_PLAYING)
				{
					std::vector<short> proximityData = Proximity(voiceData, talker, entity);
					VoicePacket_t newPacket = Speex::Encode(proximityData);
					newPacket.talker = packet->talker;
					packet = &newPacket;
				}
				if (!SV_ClientHasClientMuted(i, talker->s.number) && SV_ClientWantsVoiceData(i))
					SV_QueueVoicePacket(talker->s.number, i, packet);
			}
		}
	}

	void Voice::Frame()
	{
		Stream();
	}
}

C_EXTERN
{
	void SR_BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		SR->Server->Voice->BroadcastVoice(talker, packet);
	}
}
