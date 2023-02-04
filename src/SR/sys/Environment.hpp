#pragma once
#include "Macros.hpp"
#include <filesystem>
#include <string>

C_EXTERN
{
	#include <filesystem.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Environment variables.
	class Environment
	{
	public:
		inline static std::filesystem::path BaseDirectory;
		inline static std::filesystem::path ModDirectory;

		/// @brief Build the environment.
		static void Build();

		/// @brief Build unix/windows path.
		/// @param path - The path.
		/// @return
		static std::string BuildPath(std::string path);
	};
}
