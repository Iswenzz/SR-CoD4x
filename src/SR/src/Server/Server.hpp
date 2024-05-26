#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Server class.
	class Server
	{
	public:
		/// @brief Spawn the server.
		/// @param levelName - The level name.
		static void Spawn(const std::string& levelName);

		/// @brief Server fast restart.
		static void Restart();

		/// @brief The server render frame.
		static void Frame();
	};
}
