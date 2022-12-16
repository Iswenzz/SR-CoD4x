#include "MP3.hpp"
#include "WAV.hpp"
#include "utils/Log.hpp"

#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION

#include <minimp3_ex.h>

namespace Iswenzz::CoD4x
{
	MP3::MP3(std::string filepath)
	{
		FilePath = filepath;
		Open();
	}

	void MP3::Open()
	{
		if (!std::filesystem::exists(FilePath))
			return;

		mp3dec_t mp3d;
    	mp3dec_init(&mp3d);

		mp3dec_file_info_t fileInfo;
		if (mp3dec_load(&mp3d, FilePath.c_str(), &fileInfo, nullptr, nullptr) || !fileInfo.buffer)
		{
			Log::WriteLine("[MP3] Error opening %s", FilePath.c_str());
			return;
		}
		int channels = 1;
		int downRate = 8000;

		Rate = fileInfo.hz;
		Samples = fileInfo.samples;

		std::vector<short> monoData = Audio::StereoToMono(fileInfo.buffer, fileInfo.samples);
		Buffer = Audio::Resample(monoData.data(), monoData.size(), channels, fileInfo.hz, downRate);
		FileSize = Buffer.size() * channels;

		free(fileInfo.buffer);
	}

	void MP3::Save()
	{
		if (!Buffer.size())
			return;

		Output.open("test.wav", std::ios_base::binary);
		WAV::WriteHeader(Output, 1, 8000, Buffer.size());

		Output.write(reinterpret_cast<char*>(Buffer.data()), Buffer.size());
	}
}
