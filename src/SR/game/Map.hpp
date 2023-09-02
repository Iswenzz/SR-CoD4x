#pragma once
#include <string>

namespace Iswenzz::CoD4x
{
	/// @brief Map container.
	class Map
	{
	public:
		std::string AmbientAlias;
		int AmbientVolume = 0;
		bool AmbientStarted = false;

		/// @brief Construct a new Map instance.
		Map() = default;
		~Map() = default;

		/// @brief Map server restart.
		void Restart();

		/// @brief Map ambient sound.
		void Ambient();

		/// @brief Set the map ambient sound.
		/// @param alias - The sound alias.
		/// @param volume - The volume.
		void SetAmbient(std::string alias, int volume);

		/// @brief The map render frame.
		void Frame();
	};
}
