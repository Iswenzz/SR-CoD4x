#pragma once
#include "Base.hpp"

#include "Audio/Speex.hpp"
#include "Network/Netchan.hpp"
#include "Server/Debug.hpp"
#include "Server/Server.hpp"
#include "System/AsyncHandler.hpp"
#include "System/Environment.hpp"
#include "System/ThreadPool.hpp"
#include "Utils/Log.hpp"
#include "Utils/Utils.hpp"

#include "Commands/Container.hpp"
#include "Demo/DemoContainer.hpp"
#include "Demo/DemoRecord.hpp"
#include "Entity/Entity.hpp"
#include "Player/Player.hpp"

namespace Iswenzz::CoD4x
{
	/// @brief Game server.
	class Application
	{
	public:
		std::unique_ptr<class Server> Server;
		std::unique_ptr<class Netchan> Netchan;
		std::unique_ptr<class DemoContainer> DemoContainer;
		std::unique_ptr<class ThreadPool> ThreadPool;

		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{};
		std::array<std::shared_ptr<Entity>, MAX_GENTITIES> Entities{};

		/// @brief Server module initialization.
		Application();
		~Application();
	};
}

extern Application *SR;
