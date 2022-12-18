#include "MP3.hpp"
#include "WAV.hpp"
#include "utils/Log.hpp"

#define MINIMP3_ONLY_MP3
#define MINIMP3_NO_SIMD
#define MINIMP3_IMPLEMENTATION

#include <minimp3_ex.h>

namespace Iswenzz::CoD4x
{
	MP3::MP3(std::string filepath)
	{
		FilePath = filepath;

		AsyncCall(this, OpenAsync, &AsyncNull);
	}

	void MP3::Open()
	{
		if (!std::filesystem::exists(FilePath))
			return;

		IsLoaded = false;
		mp3dec_t mp3d;
    	mp3dec_init(&mp3d);

		Log::WriteLine("[MP3] Opening %s", FilePath.c_str());

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
		ProcessPackets();
		IsLoaded = true;
	}

	void MP3::OpenAsync(uv_work_t *req)
	{
		MP3* mp3 = reinterpret_cast<MP3*>(req->data);
		mp3->Open();
	}

	void MP3::Save(std::string path)
	{
		if (!Buffer.size())
			return;

		Output.open(path, std::ios_base::binary);
		WAV::WriteHeader(Output, 1, 8000, Buffer.size() * sizeof(short));

		Output.write(reinterpret_cast<char*>(Buffer.data()), Buffer.size() * sizeof(short));
	}
}
