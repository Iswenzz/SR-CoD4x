#pragma once
#include "Demo.hpp"

#include <mutex>

namespace SR
{
	class DemoContainer
	{
	public:
		static inline std::vector<std::string> Directories{};
		static inline std::map<std::string, Ref<Demo>> Demos{};
		static inline std::mutex Mutex;

		static void Initialize();

		static void RegisterDemoFolder(const std::filesystem::path &path);
		static int RegisterSpeedrunDemo(const std::string &map, const std::string &playerId, const std::string &run,
			const std::string &mode, const std::string &way);
	};
}
