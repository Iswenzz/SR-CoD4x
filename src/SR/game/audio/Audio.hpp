#pragma once
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
	};
}
