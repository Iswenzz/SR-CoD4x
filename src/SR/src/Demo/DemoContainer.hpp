#pragma once
#include "Demo.hpp"

namespace SR
{
	class DemoContainer
	{
	public:
		static inline std::vector<std::string> Directories{};
		static inline std::map<std::string, Ref<Demo>> Demos{};
		static inline uv_mutex_t Mutex;

		static void Initialize();

		static void RegisterDemoFolder(const std::filesystem::path &path);
		static int RegisterSpeedrunDemo(const std::string &map, const std::string &playerId, const std::string &run,
			const std::string &mode, const std::string &way);
	};
}
