#pragma once
#include <filesystem.h>
#include <filesystem>
#include <string>

namespace Iswenzz::CoD4x
{
	/// @brief Environment variables.
	class Environment
	{
	public:
		static inline std::filesystem::path BaseDirectory;
		static inline std::filesystem::path ModDirectory;

		/// @brief Build the environment.
		static void Build();

		/// @brief Build unix/windows path.
		/// @param path - The path.
		/// @return
		static std::string BuildPath(std::string path);
	};
}
