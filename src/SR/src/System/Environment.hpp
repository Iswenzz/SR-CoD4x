#pragma once
#include "Base.hpp"

#include <filesystem>

namespace SR
{
	class Environment
	{
	public:
		static inline std::filesystem::path BaseDirectory;
		static inline std::filesystem::path ModDirectory;

		static void Build();
		static std::string BuildPath(std::string path);
	};
}
