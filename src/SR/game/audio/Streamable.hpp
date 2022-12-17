#pragma once
#include "Macros.hpp"
#include "Audio.hpp"
#include "Speex.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

C_EXTERN
{
	#include <server.h>
}

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

		std::vector<VoicePacket_t> StreamPackets;
		int StreamPosition = 0;
		bool IsLoaded = false;

		/// @brief Initialize streamable audio.
		Streamable() = default;
		virtual ~Streamable();

		/// @brief Open a file.
		virtual void Open() = 0;

		/// @brief Save file.
		/// @param path - The file path.
		virtual void Save(std::string path) = 0;

		/// @brief Play the stream buffer in fragments.
		/// @return
		VoicePacket_t Play();

		/// @brief Process the buffer into streamable packets.
		void ProcessPackets();

		/// @brief Is stream end.
		/// @return
		bool IsStreamEnd();
	};
}
