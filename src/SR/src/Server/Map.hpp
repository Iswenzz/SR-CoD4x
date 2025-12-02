#pragma once
#include "Base.hpp"

namespace SR
{
	class Map
	{
	public:
		static inline std::string AmbientAlias;
		static inline int AmbientVolume = 0;
		static inline bool AmbientStarted = false;

		static void Restart();
		static void Ambient();
		static void SetAmbient(const std::string& alias, int volume);
		static void Frame();
	};
}
