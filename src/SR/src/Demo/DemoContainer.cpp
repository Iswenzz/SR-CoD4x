#include "DemoContainer.hpp"

#include "System/Environment.hpp"
#include "Utils/Log.hpp"

#include <CoD4DM1/Crypt/Huffman.hpp>

namespace SR
{
	void DemoContainer::Initialize()
	{
		Iswenzz::CoD4::DM1::Huffman::InitMain();

		Cvar_RegisterInt("sr_demo_version", 2, 0, 100, CVAR_ROM | CVAR_SERVERINFO, "SR demo version");

		RegisterDemoFolder(Environment::ModDirectory / "demos");
		RegisterDemoFolder(Environment::ModDirectory / "wrs");

		uv_mutex_init(&Mutex);
	}

	void DemoContainer::RegisterDemoFolder(const std::filesystem::path &path)
	{
		Directories.push_back(path.string());
	}

	int DemoContainer::RegisterSpeedrunDemo(const std::string &map, const std::string &playerId, const std::string &run,
		const std::string &mode, const std::string &way)
	{
		std::vector<std::string> demos{};
		for (const std::string &folder : Directories)
		{
			auto demoDirectory = std::filesystem::path(folder) / playerId / map;
			if (!std::filesystem::exists(demoDirectory))
				continue;

			for (const auto &entry : std::filesystem::directory_iterator(demoDirectory.string()))
			{
				const std::string &entryName = entry.path().filename().string();
				if (entryName == run + ".dm_1" || entryName.find(run + "_") != std::string::npos)
					demos.push_back(entry.path().string());
			}
		}
		if (demos.size())
		{
			std::string id = fmt("times_%s_%s", mode.c_str(), way.c_str());
			auto found = Demos.find(id);

			if (found != std::end(Demos))
			{
				if (!found->second->IsLoaded)
					return 2;
				Demos.erase(id);
			}
			Demos.insert({ id, CreateRef<Demo>(id, demos.at(0)) });
			Log::WriteLine("[DemoContainer] Register demo %s %s", id.c_str(), demos.at(0).c_str());
			return 1;
		}
		return 0;
	}
}
