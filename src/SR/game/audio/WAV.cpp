#include "WAV.hpp"
#include "Speex.hpp"

namespace Iswenzz::CoD4x
{
	WAV::WAV(std::string filepath)
	{
		FilePath = filepath;
	}

	void WAV::WriteHeader(int channels, int rate, int samples)
	{
		Output.seekp(0, Output.end);
		int fileSize = Output.tellp();
		Output.seekp(0, Output.beg);

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

		Output.write(reinterpret_cast<char *>(&wav), sizeof(wav));
	}
}
