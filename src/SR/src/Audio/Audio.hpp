#pragma once
#include "Base.hpp"

#include <vector>

namespace Iswenzz::CoD4x
{
	/// @brief Process audio data.
	class Audio
	{
	public:
		/// @brief Amplify audio data.
		/// @param data - The audio data.
		/// @param multiplier - The multiplier.
		/// @return
		static std::vector<short> Amplify(std::vector<short> &data, float multiplier);

		/// @brief Stereo to mono data.
		/// @param data - The stereo data.
		/// @param samples - The samples count.
		/// @return
		static std::vector<short> StereoToMono(short *data, int samples);

		/// @brief Resample PCM data.
		/// @param buffer - The PCM data.
		/// @param samples - The samples count.
		/// @param channels - The channels number.
		/// @param rate - The current sample rate.
		/// @param newRate - The new sample rate.
		/// @return
		static std::vector<short> Resample(short *buffer, int samples, int channels, int rate, int newRate);
	};
}
