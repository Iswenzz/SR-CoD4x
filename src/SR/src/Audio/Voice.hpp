#pragma once
#include "Streamable.hpp"

extern cvar_t *voice_localEcho;
extern cvar_t *voice_global;
extern cvar_t *voice_deadChat;

namespace SR
{
	/// @brief Server voice chat.
	class Voice
	{
	public:
		static inline std::map<std::string, Ref<Streamable>> Audios;
		static inline Ref<Streamable> Radio = nullptr;
		static inline int RadioFragments = 0;

		/// @brief Stream audio.
		static void Stream();

		/// @brief Proximity voice distance between the talker and the entity.
		/// @param data - The voice data.
		/// @param talker - The talker entity.
		/// @param entity - The entity.
		/// @return
		static std::vector<short> Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity);

		/// @brief Broadcast voice packets.
		/// @param talker - The talker entity.
		/// @param packet - The voice packets.
		static void BroadcastVoice(gentity_t *talker, VoicePacket_t *packet);

		/// @brief Voice server frame.
		static void Frame();
	};
}
