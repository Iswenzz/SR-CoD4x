#pragma once
#include "Macros.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>

#include <speex/speex.h>

C_EXTERN
{
	#include <server.h>
}

extern cvar_t* voice_localEcho;
extern cvar_t* voice_global;
extern cvar_t* voice_deadChat;

#define VOICE_RATE 8000
#define VOICE_FRAME_SIZE 160
#define VOICE_CHANNELS 1
#define VOICE_PCM 1
#define VOICE_PCM_CHUNK 16
#define VOICE_BITS_PER_SAMPLE 16

typedef struct
{
	uint8_t riff[4];				// Header "RIFF"
	uint32_t chunkSize;				// FileSize - 8
	uint8_t wave[4];				// Header "WAVE"
	uint8_t fmt[4];					// Header "fmt "
	uint32_t subchunk1Size;			// Size of the fmt chunk 16=PCM
	uint16_t audioFormat;			// Audio format 1=PCM, 6=mulaw, 7=alaw, 257=IBM, Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t numChannels;			// Number of channels 1=Mono 2=Stereo
	uint32_t sampleRate;			// Sampling Frequency in Hz
	uint32_t byteRate;				// SampleRate * NumChannels * BitsPerSample / 8
	uint16_t blockAlign;			// NumChannels * BitsPerSample / 8
	uint16_t bitsPerSample;			// Number of bits per sample
	uint8_t subchunk2ID[4]; 		// Section "data" string
	uint32_t subchunk2Size;			// NumSamples * NumChannels * BitsPerSample / 8
} WavHeader;

namespace Iswenzz::CoD4x
{
	/// @brief Server voice chat.
	class Voice
	{
	public:
		void *Decoder;
		void *Encoder;
		SpeexBits Bits;

		/// @brief Initialize the voice chat.
		Voice();
		~Voice();

		/// @brief Decode a speex packet.
		/// @param buffer - The speex buffer.
		/// @param maxLength - The speex data length.
		/// @param out - The output PCM buffer.
		/// @param frameSize - The frame size.
		/// @return
		int SpeexDecode(char* buffer, int maxLength, short* out, int frameSize);

		/// @brief Encode a speex packet.
		/// @param buffer - The PCM buffer.
		/// @param frameSize - The frame size.
		/// @param out - The output speex data.
		/// @return
		int SpeexEncode(short *buffer, int frameSize, char* out);

		/// @brief Decode a packet.
		/// @param packet - The packet.
		/// @return
		std::vector<short> DecodePacket(VoicePacket_t *packet);

		/// @brief Encode a packet.
		/// @param packet - The packet.
		/// @return
		VoicePacket_t EncodePacket(std::vector<short> &packet);

		/// @brief Proximity voice distance between the talker and the entity.
		/// @param data - The voice data.
		/// @param talker - The talker entity.
		/// @param entity - The entity.
		/// @return
		std::vector<short> Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity);

		/// @brief Amplify audio data.
		/// @param data - The audio data.
		/// @param multiplier - The multiplier.
		/// @return
		std::vector<short> Amplify(std::vector<short> &data, float multiplier);

		/// @brief Broadcast voice packets.
		/// @param talker - The talker entity.
		/// @param packet - The voice packets.
		void BroadcastVoice(gentity_t *talker, VoicePacket_t *packet);

		/// @brief Write WAV header.
		/// @param file - The wav file.
		/// @param channels - Number of channels.
		/// @param rate - The wav samples rate.
		/// @param samples - The wav samples count.
		void WriteHeaderWAV(std::ofstream &file, int channels, int rate, int samples);
	};
}
