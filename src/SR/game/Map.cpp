#include "Map.hpp"
#include "SR.hpp"

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

	void Map::Frame()
	{
		Ambient();
	}
}
