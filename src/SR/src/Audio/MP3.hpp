#pragma once
#include "Streamable.hpp"

namespace SR
{
	/// @brief MP3 audio file.
	class MP3 : public Streamable
	{
		IZ_ASYNC(OpenAsync)
	public:
		/// @brief Open a MP3 file.
		/// @param filepath - The file path.
		MP3(const std::string& filepath);
		virtual ~MP3() = default;

		/// @brief Open a file.
		void Open() override;

		/// @brief Save file.
		/// @param path - The file path.
		void Save(const std::string& path) override;
	};
}
