#pragma once
#include "Streamable.hpp"

struct WavHeader
{
	uint8_t riff[4];		// Header "RIFF"
	uint32_t chunkSize;		// FileSize - 8
	uint8_t wave[4];		// Header "WAVE"
	uint8_t fmt[4];			// Header "fmt "
	uint32_t subchunk1Size; // Size of the fmt chunk 16=PCM
	uint16_t audioFormat;	// Audio format 1=PCM, 6=mulaw, 7=alaw, 257=IBM, Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t numChannels;	// Number of channels 1=Mono 2=Stereo
	uint32_t sampleRate;	// Sampling Frequency in Hz
	uint32_t byteRate;		// SampleRate * NumChannels * BitsPerSample / 8
	uint16_t blockAlign;	// NumChannels * BitsPerSample / 8
	uint16_t bitsPerSample; // Number of bits per sample
	uint8_t subchunk2ID[4]; // Section "data" string
	uint32_t subchunk2Size; // NumSamples * NumChannels * BitsPerSample / 8
};

namespace SR
{
	class WAV : public Streamable
	{
	public:
		WAV(const std::string& filepath);
		virtual ~WAV() = default;

		void Open(const Ref<AsyncTask>& task) override;
		void Save(const std::string& path);

	private:
		void WriteHeader(std::ofstream& file, int channels, int rate, int samples);
	};
}
