#include "MP3.hpp"
#include "WAV.hpp"
#include "utils/Log.hpp"

#define MINIMP3_ONLY_MP3
#define MINIMP3_NO_STDIO
#define MINIMP3_IMPLEMENTATION

#include <minimp3_ex.h>

namespace Iswenzz::CoD4x
{
	MP3::MP3(std::string filepath)
	{
		FilePath = filepath;

		AsyncWorker(this, OpenAsync, NULL, NULL);
	}

	void MP3::Open()
	{
		if (!std::filesystem::exists(FilePath))
			return;

		IsLoaded = false;
		mp3dec_t mp3d;
    	mp3dec_init(&mp3d);

		Input.open(FilePath, std::ios_base::binary);
		Log::WriteLine("[MP3] Opening %s", FilePath.c_str());

		Input.seekg(0, Input.end);
		FileSize = Input.tellg();
		Input.seekg(0, Input.beg);

		std::vector<unsigned char> buffer(FileSize);
		Input.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

		mp3dec_file_info_t fileInfo;
		if (mp3dec_load_buf(&mp3d, buffer.data(), buffer.size(), &fileInfo, nullptr, nullptr))
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

		free(fileInfo.buffer);
		ProcessPackets();
		IsLoaded = true;
	}

	void MP3::OpenAsync(uv_work_t *req)
	{
		MP3* mp3 = reinterpret_cast<MP3*>(AsyncWorkerData(req));
		mp3->Open();

		AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
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
