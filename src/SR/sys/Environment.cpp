#include "Environment.hpp"

namespace Iswenzz::CoD4x
{
	void Environment::Build()
	{
		BaseDirectory = BuildPath(fs_basepath->string);
		ModDirectory = BaseDirectory / BuildPath(std::string(fs_gameDirVar->string));
	}

	std::string Environment::BuildPath(std::string path)
	{
		#ifdef _WIN32
			std::replace(path.begin(), path.end(), '/', '\\');
		#else
			std::replace(path.begin(), path.end(), '\\', '/');
		#endif
		return path;
	}
}
