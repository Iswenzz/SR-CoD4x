#pragma once
#include "Streamable.hpp"

namespace Iswenzz::CoD4x
{
	/// @brief MP3 audio file.
	class MP3 : public Streamable
	{
	public:
		/// @brief Open a MP3 file.
		/// @param filepath - The file path.
		MP3(std::string filepath);
		virtual ~MP3() = default;

		/// @brief Open a file.
		void Open() override;

		/// @brief Save file.
		void Save() override;
	};
}
