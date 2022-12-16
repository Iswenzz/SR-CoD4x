#include "WAV.hpp"
#include "Speex.hpp"

namespace Iswenzz::CoD4x
{
	WAV::WAV(std::string filepath)
	{
		FilePath = filepath;
		Open();
	}

	void WAV::Open()
	{
		if (!std::filesystem::exists(FilePath))
			return;
		Input.open(FilePath, std::ios_base::binary);

		WavHeader header;
		Input.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
		Buffer.resize(FileSize);

		Samples = header.subchunk2Size;
		Rate = header.sampleRate;

		int channels = 1;
		int downRate = 8000;

		std::vector<short> pcm(Samples / sizeof(short));
		Input.read(reinterpret_cast<char*>(pcm.data()), Samples);

		std::vector<short> monoData = Audio::StereoToMono(pcm.data(), pcm.size());
		Buffer = Audio::Resample(monoData.data(), monoData.size(), channels, Rate, downRate);
	}

	void WAV::Save()
	{
		if (!Buffer.size())
			return;

		Output.open("test.wav", std::ios_base::binary);
		WAV::WriteHeader(Output, 1, 8000, Buffer.size());

		Output.write(reinterpret_cast<char*>(Buffer.data()), Buffer.size());
	}

	void WAV::WriteHeader(std::ofstream &file, int channels, int rate, int samples)
	{
		file.seekp(0, file.end);
		int fileSize = file.tellp();
		file.seekp(0, file.beg);

		WavHeader wav;
		std::memcpy(&wav.riff, "RIFF", 4);
		wav.chunkSize = fileSize + sizeof(WavHeader) - 8;
		std::memcpy(&wav.wave, "WAVE", 4);
		std::memcpy(&wav.fmt, "fmt ", 4);
		wav.subchunk1Size = SPEEX_PCM_CHUNK;
		wav.audioFormat = SPEEX_PCM;
		wav.numChannels = channels;
		wav.sampleRate = rate;
		wav.bitsPerSample = SPEEX_BITS_PER_SAMPLE;
		wav.byteRate = wav.sampleRate * wav.numChannels * wav.bitsPerSample / 8;
		wav.blockAlign = wav.numChannels * wav.bitsPerSample / 8;
		std::memcpy(&wav.subchunk2ID, "data", 4);
		wav.subchunk2Size = samples;

		file.write(reinterpret_cast<char *>(&wav), sizeof(wav));
	}
}
