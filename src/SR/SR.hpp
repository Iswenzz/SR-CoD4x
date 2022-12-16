#pragma once
#include "Macros.hpp"

#include "game/demo/DemoContainer.hpp"
#include "game/audio/Speex.hpp"

#include "game/Server.hpp"
#include "game/Entity.hpp"
#include "game/Debug.hpp"

#include "net/Netchan.hpp"
#include "commands/Container.hpp"
#include "player/Player.hpp"

#include "utils/Log.hpp"
#include "utils/Environment.hpp"

namespace Iswenzz::CoD4x
{
	/// @brief Game server.
	class Game
	{
	public:
		std::unique_ptr<class Server> Server;
		std::unique_ptr<class Netchan> Netchan;
		std::unique_ptr<class DemoContainer> DemoContainer;

		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{ };
		std::array<std::shared_ptr<Entity>, MAX_GENTITIES> Entities{ };

		/// @brief Server module initialization.
		Game();
		~Game();
	};
}

using namespace Iswenzz::CoD4x;
extern Game *SR;
