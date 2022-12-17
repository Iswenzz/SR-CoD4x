#pragma once
#include "Macros.hpp"
#include "Streamable.hpp"

#include <vector>
#include <map>

C_EXTERN
{
	#include <server.h>
}

extern cvar_t* voice_localEcho;
extern cvar_t* voice_global;
extern cvar_t* voice_deadChat;

namespace Iswenzz::CoD4x
{
	/// @brief Server voice chat.
	class Voice
	{
	public:
		std::map<std::string, std::shared_ptr<Streamable>> Audios;
		std::shared_ptr<Streamable> Radio;
		int RadioFragments = 0;

		/// @brief Initialize the voice chat.
		Voice() = default;
		~Voice() = default;

		/// @brief Stream audio.
		void Stream();

		/// @brief Proximity voice distance between the talker and the entity.
		/// @param data - The voice data.
		/// @param talker - The talker entity.
		/// @param entity - The entity.
		/// @return
		std::vector<short> Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity);

		/// @brief Broadcast voice packets.
		/// @param talker - The talker entity.
		/// @param packet - The voice packets.
		void BroadcastVoice(gentity_t *talker, VoicePacket_t *packet);

		/// @brief Voice server frame.
		void Frame();
	};
}
