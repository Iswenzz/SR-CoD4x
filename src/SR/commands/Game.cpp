#include "Game.hpp"
#include "SR.hpp"

#include "game/audio/WAV.hpp"
#include "game/audio/MP3.hpp"

#include <filesystem>
#include <map>

namespace Iswenzz::CoD4x
{
	void GameCommands::Register()
	{
		Scr_AddFunction("legacyweapon", LegacyWeapon, qfalse);
		Scr_AddFunction("isprecached", IsPrecached, qfalse);
		Scr_AddFunction("radioplay", RadioPlay, qfalse);
	}

	void GameCommands::IsPrecached()
	{
		CHECK_PARAMS(2, "Usage: IsPrecached(<name>, <type>)");

		const char *name = Scr_GetString(0);
		std::string type = Scr_GetString(1);

		if (type == "item")
			Scr_AddInt(G_FindItem(name, 0));
		else if (type == "material")
			Scr_AddInt(G_FindMaterial(name) >= 0);
		else
			Scr_AddInt(-1);
	}

	void GameCommands::LegacyWeapon()
	{
		CHECK_PARAMS(1, "Usage: LegacyWeapon(<name>)");

		static const std::map<std::string, std::string> legacyWeapons = {
			{ "brecci_mp", "winchester1200_grip_mp" },
			{ "remington700_silencer_mp", "winchester1200_reflex_mp" },
			{ "mg42_mp", "mp5_reflex_mp" },
			{ "chainsaw_mp", "mp5_acog_mp" },
			{ "beretta_tactical_mp", "mp5_silencer_mp" },
			{ "olympia_mp", "saw_acog_mp" },
			{ "shovel_mp", "saw_mp" },
			{ "wavegun_mp", "m60e4_grip_mp" },
			{ "fn_rpg_mp", "m60e4_acog_mp" },
			{ "bt_rpg_mp", "m60e4_reflex_mp" },
			{ "pps42_mp", "saw_reflex_mp" },
			{ "shop_mp", "cobra_FFAR_mp" },
			{ "vip_mp", "cobra_20mm_mp" },
			{ "rtd_mp", "hind_FFAR_mp" },
			{ "owner_mp", "airstrike_mp" },
			{ "shepherd_mp", "artillery_mp" }
		};
		const char *name = Scr_GetString(0);
		auto newName = legacyWeapons.find(name);

		Scr_AddString(newName != std::end(legacyWeapons) ? newName->second.c_str() : name);
	}

	void GameCommands::RadioPlay()
	{
		CHECK_PARAMS(2, "Usage: RadioPlay(<name>, <type>)");

		std::string name = Scr_GetString(0);
		std::string type = Scr_GetString(1);

		if (name == "stop")
		{
			SR->Server->Voice->Radio = nullptr;
			return;
		}
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

		auto streamable = SR->Server->Voice->Audios.find(name);
		if (streamable == std::end(SR->Server->Voice->Audios))
		{
			if (type == "wav")
				file = std::make_shared<WAV>(name);
			else if (type == "mp3")
				file = std::make_shared<MP3>(name);
			SR->Server->Voice->Audios.insert({ name, file });
		}
		else
			file = streamable->second;

		file->StreamPosition = 0;
		SR->Server->Voice->Radio = file;

		Log::WriteLine("[Radio] Playing %s", name.c_str());
	}
}
