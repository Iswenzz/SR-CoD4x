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

		/// @brief Open a file.
		/// @param req - The worker request.
		static void OpenAsync(uv_work_t *req);

		/// @brief Save file.
		/// @param path - The file path.
		void Save(std::string path) override;
	};
}
