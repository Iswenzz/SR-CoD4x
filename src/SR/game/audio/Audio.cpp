#include "Audio.hpp"
#include <samplerate.h>

namespace Iswenzz::CoD4x
{
	std::vector<short> Audio::Amplify(std::vector<short> &data, float multiplier)
	{
		std::vector<short> dataAmplified(data.size());
		for (int i = 0; i < data.size(); i++)
		{
			int amplified = data[i] * multiplier;

			if (amplified > SHRT_MAX)
				amplified = SHRT_MAX;
			else if (amplified < SHRT_MIN)
				amplified = SHRT_MIN;

			dataAmplified[i] = static_cast<short>(amplified);
		}
		return dataAmplified;
	}
}
