#pragma once
#include "game/Map.hpp"
#include "game/Vegas.hpp"
#include "game/audio/Voice.hpp"

#include <sys_main.h>

namespace Iswenzz::CoD4x
{
	/// @brief Server container.
	class Server
	{
	public:
		std::unique_ptr<class Map> Map;
		std::unique_ptr<class Voice> Voice;
		std::unique_ptr<class Vegas> Vegas;

		/// @brief Construct a new Server instance.
		Server();
		~Server() = default;

		/// @brief Spawn the server.
		/// @param levelName - The level name.
		void Spawn(std::string levelName);

		/// @brief Server fast restart.
		void Restart();

		/// @brief The server render frame.
		void Frame();
	};
}
