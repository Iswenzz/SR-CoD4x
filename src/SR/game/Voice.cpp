#include "Voice.hpp"
#include "SR.hpp"

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

	void Voice::BroadcastVoice(struct gentity_s *entity, VoicePacket_t *packet)
	{
		int i;
		struct gentity_s* ent;

		std::vector<short> soundData = DecodePacket(packet);
		VoicePacket_t newPacket = EncodePacket(soundData);
		newPacket.talker = packet->talker;

		entity->client->lastVoiceTime = level.time;

		for (i = 0, ent = level.gentities; i < level.maxclients; i++, ent++)
		{
			if (ent->client && ent->client->sess.sessionState != SESS_STATE_INTERMISSION)
			{
				if (!voice_localEcho->boolean && ent == entity)
					continue;
				if (!voice_global->boolean && !OnSameTeam(ent, entity))
					continue;
				if (!voice_deadChat->boolean && ent->client->sess.sessionState == SESS_STATE_DEAD)
					continue;

				if (!SV_ClientHasClientMuted(i, entity->s.number) && SV_ClientWantsVoiceData(i))
					SV_QueueVoicePacket(entity->s.number, i, &newPacket);
			}
		}
	}

	void Voice::WriteHeaderWAV(std::ofstream &file, int dataSize, int samplesCount)
	{
		file.seekp(0, file.beg);

		WavHeader wav;
		std::memcpy(&wav.riff, "RIFF", 4);
		wav.chunkSize = dataSize + sizeof(WavHeader) - 8;
		std::memcpy(&wav.wave, "WAVE", 4);
		std::memcpy(&wav.fmt, "fmt ", 4);
		wav.subchunk1Size = VOICE_PCM_CHUNK;
		wav.audioFormat = VOICE_PCM;
		wav.numChannels = VOICE_CHANNELS;
		wav.sampleRate = VOICE_RATE;
		wav.byteRate = VOICE_RATE * VOICE_CHANNELS * VOICE_BITS_PER_SAMPLE / 8;
		wav.blockAlign = VOICE_CHANNELS * VOICE_BITS_PER_SAMPLE / 8;
		wav.bitsPerSample = VOICE_BITS_PER_SAMPLE;
		std::memcpy(&wav.subchunk2ID, "data", 4);
		wav.subchunk2Size = samplesCount;

		file.write(reinterpret_cast<char *>(&wav), sizeof(wav));
	}
}

C_EXTERN
{
	void SR_BroadcastVoice(struct gentity_s *entity, VoicePacket_t *packet)
	{
		SR->Server->Voice->BroadcastVoice(entity, packet);
	}
}
