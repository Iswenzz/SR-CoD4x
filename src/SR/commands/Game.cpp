#include "Game.hpp"
#include "SR.hpp"

#include "game/audio/WAV.hpp"
#include "game/audio/MP3.hpp"

#include <filesystem>

namespace Iswenzz::CoD4x
{
	void GameCommands::Register()
	{
		Scr_AddFunction("radioplay", RadioPlay, qfalse);
	}

	void GameCommands::RadioPlay()
	{
		CHECK_PARAMS(2, "Usage: RadioPlay(<name>, <type>)");

		std::string name = Scr_GetString(0);
		std::string type = Scr_GetString(1);

		if (type != "mp3" && type != "wav")
		{
			Scr_ObjectError("Radio type is wav or mp3.\n");
			return;
		}
		if (!std::filesystem::exists(name))
		{
			Scr_ObjectError(fmt("Radio file name %s doesn't exists.\n", name));
			return;
		}
		std::shared_ptr<Streamable> file;

		if (type == "wav")
			file = std::make_shared<WAV>(name);
		else if (type == "mp3")
			file = std::make_shared<MP3>(name);

		if (SR->Server->Voice->Audios.find(name) != std::end(SR->Server->Voice->Audios))
			SR->Server->Voice->Audios.insert({ name, file });
		SR->Server->Voice->Radio = file;
	}
}
