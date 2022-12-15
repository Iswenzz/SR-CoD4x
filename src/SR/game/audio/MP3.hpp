#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

namespace Iswenzz::CoD4x
{
	/// @brief MP3 audio file.
	class MP3
	{
	public:
		std::ifstream Input;
		std::ofstream Output;

		std::string FilePath;

		/// @brief Open a MP3 file.
		/// @param filepath - The file path.
		MP3(std::string filepath);
		~MP3();
	};
}
