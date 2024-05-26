#pragma once
#include "Demo.hpp"

namespace SR
{
	/// @brief Demo container class.
	class DemoContainer
	{
	public:
		static inline std::vector<std::string> Directories{};
		static inline std::map<std::string, Ref<Demo>> Demos{};
		static inline uv_mutex_t Mutex;

		/// @brief Initialize the DemoContainer.
		static void Initialize();

		/// @brief Register a demo folder.
		/// @param path - The folder path.
		static void RegisterDemoFolder(const std::filesystem::path &path);

		/// @brief Register a speedrun demo.
		/// @param map - The map name.
		/// @param playerId - The player id.
		/// @param run - The run id.
		/// @param mode - The run mode.
		/// @param way - The run way.
		static int RegisterSpeedrunDemo(const std::string &map, const std::string &playerId, const std::string &run,
			const std::string &mode, const std::string &way);
	};
}
