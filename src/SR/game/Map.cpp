#include "Map.hpp"

namespace Iswenzz::CoD4x
{
	void Map::Restart()
	{
		AmbientAlias = "";
		AmbientVolume = 0;
		AmbientStarted = false;
	}

	void Map::Ambient()
	{
		if (AmbientStarted)
			return;
		AmbientStarted = true;

		SV_SetConfigstring(0x335, fmt("n\\%s\\t\\%i", AmbientAlias.c_str(), AmbientVolume));
	}

	void Map::SetAmbient(std::string alias, int volume)
	{
		if (AmbientStarted)
			return;

		AmbientAlias = alias;
		AmbientVolume = volume + 1000;
	}

	void Map::Frame()
	{
		Ambient();
	}
}
