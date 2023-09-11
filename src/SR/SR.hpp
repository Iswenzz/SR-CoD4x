#pragma once
#include "game/Definitions.hpp"
#include "game/demo/DemoContainer.hpp"
#include "game/demo/DemoRecord.hpp"
#include "game/audio/Speex.hpp"
#include "game/Server.hpp"
#include "game/Entity.hpp"
#include "game/Debug.hpp"

#include "commands/Container.hpp"
#include "player/Player.hpp"
#include "utils/Log.hpp"
#include "utils/Utils.hpp"
#include "net/Netchan.hpp"

#include "sys/AsyncHandler.hpp"
#include "sys/Environment.hpp"
#include "sys/ThreadPool.hpp"

C_EXTERN
{
	#include <server.h>
	#include <cscr_stringlist.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Game server.
	class Game
	{
	public:
		std::unique_ptr<class Server> Server;
		std::unique_ptr<class Netchan> Netchan;
		std::unique_ptr<class DemoContainer> DemoContainer;
		std::unique_ptr<class ThreadPool> ThreadPool;

		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{ };
		std::array<std::shared_ptr<Entity>, MAX_GENTITIES> Entities{ };

		/// @brief Server module initialization.
		Game();
		~Game();
	};
}

using namespace Iswenzz::CoD4x;
extern Game *SR;
