#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Map class.
	class Map
	{
	public:
		static inline std::string AmbientAlias;
		static inline int AmbientVolume = 0;
		static inline bool AmbientStarted = false;

		/// @brief Map server restart.
		static void Restart();

		/// @brief Map ambient sound.
		static void Ambient();

		/// @brief Set the map ambient sound.
		/// @param alias - The sound alias.
		/// @param volume - The volume.
		static void SetAmbient(const std::string& alias, int volume);

		/// @brief The map render frame.
		static void Frame();
	};
}
