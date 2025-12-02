#pragma once
#include "Streamable.hpp"

extern cvar_t *voice_localEcho;
extern cvar_t *voice_global;
extern cvar_t *voice_deadChat;

namespace SR
{
	class Voice
	{
	public:
		static inline std::map<std::string, Ref<Streamable>> Audios;
		static inline Ref<Streamable> Radio = nullptr;
		static inline int RadioFragments = 0;

		static void Stream();
		static std::vector<short> Proximity(std::vector<short> &data, gentity_t *talker, gentity_t *entity);
		static void BroadcastVoice(gentity_t *talker, VoicePacket_t *packet);
		static void Frame();
	};
}
