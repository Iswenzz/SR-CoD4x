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
	/// @brief Speex VoIP transmition class.
	class Speex
	{
	public:
		static inline void *Decoder = nullptr;
		static inline void *Encoder = nullptr;
		static inline SpeexBits Bits = { 0 };

		/// @brief Initialize speex encoder and decoder.
		static void Initialize();

		/// @brief Shutdown speex.
		static void Shutdown();

		/// @brief Decode a speex packet.
		/// @param packet - The packet.
		/// @return
		static std::vector<short> Decode(VoicePacket_t *packet);

		/// @brief Encode a speex packet.
		/// @param packet - The packet.
		static VoicePacket_t Speex::Encode(std::vector<short> &packet);
	};
}
