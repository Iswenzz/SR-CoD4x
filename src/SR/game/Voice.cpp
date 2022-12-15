#include "Voice.hpp"
#include "SR.hpp"

#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION

#include <minimp3_ex.h>
#include <samplerate.h>

#define VOICE_AMPLIFY 2
#define PROXIMITY_DISTANCE 1500

namespace Iswenzz::CoD4x
{
	Voice::Voice()
	{
		int enh = 1;
		int vad = 0;

		speex_bits_init(&Bits);

		Decoder = speex_decoder_init(&speex_nb_mode);
    	speex_decoder_ctl(Decoder, SPEEX_SET_ENH, &enh);

		Encoder = speex_encoder_init(&speex_nb_mode);
    	speex_encoder_ctl(Encoder, SPEEX_SET_VAD, &vad);
	}

	Voice::~Voice()
	{
		speex_bits_destroy(&Bits);
		speex_decoder_destroy(Decoder);
		speex_encoder_destroy(Encoder);
	}

	int Voice::SpeexDecode(char* buffer, int maxLength, short* out, int frameSize)
	{
		speex_bits_read_from(&Bits, buffer, maxLength);
		speex_decode_int(Decoder, &Bits, out);
		return VOICE_CHANNELS * frameSize * sizeof(short);
	}

	int Voice::SpeexEncode(short *buffer, int frameSize, char* out)
	{
		speex_bits_reset(&Bits);
		speex_encode_int(Encoder, buffer, &Bits);
		return speex_bits_write(&Bits, out, frameSize);
	}

	std::vector<short> Voice::DecodePacket(VoicePacket_t *packet)
	{
		std::vector<short> decodedData;
		decodedData.resize(VOICE_FRAME_SIZE);

		int decodedDataSize = 0;
		int packetDataSize = packet->dataSize;

		decodedDataSize = SpeexDecode(packet->data, packetDataSize, decodedData.data(), VOICE_FRAME_SIZE);
		return decodedData;
	}

	VoicePacket_t Voice::EncodePacket(std::vector<short> &packet)
	{
		VoicePacket_t encodedData;
		int packetDataSize = packet.size();

		encodedData.dataSize = SpeexEncode(packet.data(), packetDataSize, encodedData.data);
		return encodedData;
	}

	std::vector<short> Voice::Amplify(std::vector<short> &data, float multiplier)
	{
		std::vector<short> dataAmplified(data.size());
		for (int i = 0; i < data.size(); i++)
		{
			int amplified = data[i] * multiplier;

			if (amplified > SHRT_MAX)
				amplified = SHRT_MAX;
			else if (amplified < SHRT_MIN)
				amplified = SHRT_MIN;

			dataAmplified[i] = static_cast<short>(amplified);
		}
		return dataAmplified;
	}

	std::vector<short> Voice::Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity)
	{
		float distance = fabs(VectorDistance(talker->client->ps.origin, entity->client->ps.origin));

		if (distance > PROXIMITY_DISTANCE)
			distance = PROXIMITY_DISTANCE;
		distance = 1 - (distance / PROXIMITY_DISTANCE);
		distance *= VOICE_AMPLIFY;

		return Amplify(data, distance);
	}

	void Voice::BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		int i;
		gentity_t* entity;

		std::vector<short> voiceData = DecodePacket(packet);
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
				VoicePacket_t newPacket = EncodePacket(proximityData);
				newPacket.talker = packet->talker;

				if (!SV_ClientHasClientMuted(i, talker->s.number) && SV_ClientWantsVoiceData(i))
					SV_QueueVoicePacket(talker->s.number, i, &newPacket);
			}
		}
	}

	void Voice::WriteHeaderWAV(std::ofstream &file, int channels, int rate, int samples)
	{
		file.seekp(0, file.end);
		int fileSize = file.tellp();
		file.seekp(0, file.beg);

		WavHeader wav;
		std::memcpy(&wav.riff, "RIFF", 4);
		wav.chunkSize = fileSize + sizeof(WavHeader) - 8;
		std::memcpy(&wav.wave, "WAVE", 4);
		std::memcpy(&wav.fmt, "fmt ", 4);
		wav.subchunk1Size = VOICE_PCM_CHUNK;
		wav.audioFormat = VOICE_PCM;
		wav.numChannels = channels;
		wav.sampleRate = rate;
		wav.bitsPerSample = VOICE_BITS_PER_SAMPLE;
		wav.byteRate = wav.sampleRate * wav.numChannels * wav.bitsPerSample / 8;
		wav.blockAlign = wav.numChannels * wav.bitsPerSample / 8;
		std::memcpy(&wav.subchunk2ID, "data", 4);
		wav.subchunk2Size = samples;

		file.write(reinterpret_cast<char *>(&wav), sizeof(wav));
	}
}

C_EXTERN
{
	void SR_BroadcastVoice(gentity_t *talker, VoicePacket_t *packet)
	{
		SR->Server->Voice->BroadcastVoice(talker, packet);
	}
}
