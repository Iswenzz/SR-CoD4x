#pragma once
#include "Base.hpp"

#include <speex/speex.h>
#include <cstring>

#define SPEEX_RATE 8000
#define SPEEX_FRAME_SIZE 160
#define SPEEX_CHANNELS 1
#define SPEEX_PCM 1
#define SPEEX_PCM_CHUNK 16
#define SPEEX_BITS_PER_SAMPLE 16

namespace SR
{
	class Speex
	{
	public:
		static inline void *Decoder = nullptr;
		static inline void *Encoder = nullptr;
		static inline SpeexBits Bits = { 0 };

		static void Initialize();
		static void Shutdown();

		static std::vector<short> Decode(VoicePacket_t *packet);
		static VoicePacket_t Speex::Encode(std::vector<short> &packet);
	};
}
