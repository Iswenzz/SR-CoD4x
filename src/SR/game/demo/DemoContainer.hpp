#pragma once
#include "Demo.hpp"
#include <filesystem>

namespace Iswenzz::CoD4x
{
	/// @brief Demo container class.
	class DemoContainer
	{
	public:
		std::vector<std::string> Directories{ };
		std::map<std::string, std::shared_ptr<Demo>> Demos{ };

		/// @brief Initialize a DemoContainer.
		DemoContainer();
		~DemoContainer() = default;

		/// @brief Register a demo folder.
		/// @param path - The folder path.
		void RegisterDemoFolder(const std::filesystem::path &path);

		/// @brief Register a speedrun demo.
		/// @param map - The map name.
		/// @param playerId - The player id.
		/// @param run - The run id.
		/// @param mode - The run mode.
		/// @param way - The run way.
		int RegisterSpeedrunDemo(const std::string &map, const std::string &playerId, const std::string &run,
			const std::string &mode, const std::string &way);
	};
}
