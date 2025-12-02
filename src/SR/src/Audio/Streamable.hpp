#pragma once
#include "Base.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>

namespace SR
{
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

		Streamable() = default;
		virtual ~Streamable();

		virtual void Open() = 0;
		virtual void Save(const std::string& path) = 0;
		VoicePacket_t Play();

		void ProcessPackets();
		bool IsStreamEnd();
	};
}
