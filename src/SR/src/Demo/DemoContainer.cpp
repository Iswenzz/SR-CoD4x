#include "DemoContainer.hpp"

#include "System/Environment.hpp"
#include "Utils/Log.hpp"

#include <CoD4DM1/Crypt/Huffman.hpp>

namespace SR
{
	void DemoContainer::Initialize()
	{
		CoD4::DM1::Huffman::InitMain();

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
			const auto demoDirectory = std::filesystem::path(folder) / playerId / map;
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
			const auto found = Demos.find(id);

			if (found != std::end(Demos))
			{
				if (!found->second->IsLoaded)
					return 2;
				Demos.erase(id);
			}
			const auto demoPath = demos.at(0);
			const auto relativePath = std::filesystem::relative(demoPath, Environment::ModDirectory).string();
			Demos.insert({ id, CreateRef<Demo>(id, demoPath) });
			Log::WriteLine("[DemoContainer] Register demo %s %s", id.c_str(), relativePath.c_str());
			return 1;
		}
		return 0;
	}
}
