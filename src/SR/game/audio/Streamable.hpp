#pragma once
#include "Audio.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

namespace Iswenzz::CoD4x
{
	/// @brief Stream buffer over VoIP.
	class Streamable
	{
	public:
		std::string FilePath;
		int FileSize = 0;

		std::ifstream Input;
		std::ofstream Output;

		std::vector<short> Buffer;
		int Samples = 0;
		int Rate = 0;

		std::vector<short> StreamBuffer;
		int StreamPosition = 0;

		/// @brief Initialize streamable audio.
		Streamable() = default;
		virtual ~Streamable();

		/// @brief Open a file.
		virtual void Open() = 0;

		/// @brief Save file.
		virtual void Save() = 0;

		/// @brief Play the stream buffer in fragments.
		/// @return
		std::vector<short> Play();
	};
}
