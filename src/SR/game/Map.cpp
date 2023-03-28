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

		SV_SetConfigstring(0x335, va("n\\%s\\t\\%i", AmbientAlias.c_str(), AmbientVolume));
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
		if (SR->Server->Map->AmbientStarted)
			return;

		SR->Server->Map->AmbientAlias = alias;
		SR->Server->Map->AmbientVolume = volume + 1000;
	}
}
