#pragma once
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
		std::ifstream Input;
		std::ofstream Output;
		std::vector<short> Buffer;

		std::vector<short> StreamBuffer;
		int StreamPosition = 0;

		/// @brief Initialize streamable audio.
		Streamable() = default;
		virtual ~Streamable();

		/// @brief Play the stream buffer in fragments.
		/// @return
		std::vector<short> Play();
	};
}
