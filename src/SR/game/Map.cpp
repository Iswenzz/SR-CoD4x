#include "Map.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void Map::Restart()
	{
		AmbientStarted = false;
	}

	void Map::Ambient()
	{
		if (AmbientStarted)
			return;
		AmbientStarted = true;

		if (AmbientAlias.empty())
			return;

		SV_SetConfigstring(0x335, va("n\\%s\\t\\%i", AmbientAlias.c_str(), AmbientVolume));

		AmbientAlias = "";
		AmbientVolume = 0;
	}

	void Map::Frame()
	{
		Ambient();
	}
}

C_EXTERN
{
	void SR_SetMapAmbient(const char *alias, int volume)
	{
		SR->Server->Map->AmbientAlias = alias;
		SR->Server->Map->AmbientVolume = volume + 1000;
	}
}
