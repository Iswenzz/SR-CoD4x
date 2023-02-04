#include "DemoContainer.hpp"
#include "sys/Environment.hpp"
#include "utils/Log.hpp"

namespace Iswenzz::CoD4x
{
	DemoContainer::DemoContainer()
	{
		Cvar_RegisterInt("sr_demo_version", 2, 0, 100, CVAR_ROM | CVAR_SERVERINFO, "SR demo version");

		RegisterDemoFolder(Environment::ModDirectory / "demos");
		RegisterDemoFolder(Environment::ModDirectory / "wrs");
	}

	void DemoContainer::RegisterDemoFolder(const std::filesystem::path &path)
	{
		Directories.push_back(path.string());
	}

	bool DemoContainer::RegisterSpeedrunDemo(const std::string &map,
		const std::string &playerId, const std::string &run, const std::string &mode, const std::string &way)
	{
		std::vector<std::string> demos{ };
		for (const std::string& folder : Directories)
		{
			auto demoDirectory = std::filesystem::path(folder) / playerId / map;
			if (!std::filesystem::exists(demoDirectory))
				continue;

			for (const auto& entry : std::filesystem::directory_iterator(demoDirectory.string()))
			{
				const std::string& entryName = entry.path().filename().string();
				if (entryName == run + ".dm_1" || entryName.find(run + "_") != std::string::npos)
					demos.push_back(entry.path().string());
			}
		}
		if (demos.size())
		{
			std::string id = fmt("times_%s_%s", mode.c_str(), way.c_str());

			if (Demos.count(id))
				Demos.erase(id);

			Demos.insert({ id, std::make_shared<Demo>(id, demos.at(0)) });

			Log::WriteLine("[DemoContainer] Register demo %s %s", id.c_str(), demos.at(0).c_str());
		}
		return demos.size();
	}
}
