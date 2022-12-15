#pragma once
#include "game/Vegas.hpp"
#include "game/audio/Voice.hpp"

C_EXTERN
{
	#include <sys_main.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Server container.
	class Server
	{
	public:
		std::unique_ptr<class Voice> Voice;
		std::unique_ptr<class Vegas> Vegas;

		/// @brief Construct a new Server object.
		Server();
		~Server() = default;

		/// @brief Spawn the server.
		/// @param levelName - The level name.
		void Spawn(std::string levelName);

		/// @brief The server render frame.
		void Frame();
	};
}
