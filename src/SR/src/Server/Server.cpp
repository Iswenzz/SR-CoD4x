#include "Server.hpp"
#include "Map.hpp"

#include "Audio/Voice.hpp"
#include "Network/Vegas.hpp"
#include "System/Debug.hpp"

#include "Demo/DemoContainer.hpp"
#include "Entity/Entity.hpp"
#include "Player/Player.hpp"

namespace SR
{
	void Server::Spawn(const std::string& levelName)
	{
		Log::WriteLine("[Server] Spawn server");

		Async::Shutdown();
		Async::Initialize();

		Player::List = {};
		Entity::List = {};
		DemoContainer::Demos.clear();
	}

	void Server::Restart()
	{
		Map::Restart();
	}

	void Server::Frame()
	{
		for (const auto& player : Player::List)
		{
			if (player)
			{
				player->Frame();
				Vegas::Frame(player);
			}
		}
		Map::Frame();
		Voice::Frame();
		Debug::FPS();
	}
}
