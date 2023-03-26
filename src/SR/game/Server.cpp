#include "Server.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
		Map = std::make_unique<class Map>();
		Voice = std::make_unique<class Voice>();
		Vegas = std::make_unique<class Vegas>();
	}

	void Server::Spawn(std::string levelName)
	{
		Log::WriteLine("[Server] Spawn server");

		SR->ThreadPool->GSC->Restart();

		SR->Players = { };
		SR->Entities = { };

		SR->DemoContainer->Demos.clear();
	}

	void Server::Restart()
	{
		Map->Restart();
	}

	void Server::Frame()
	{
		for (const auto &player : SR->Players)
		{
			if (player)
				player->Frame();
		}
		Map->Frame();
		Voice->Frame();
		Debug::FPS();
	}
}

C_EXTERN
{
	void SR_Frame()
	{
		SR->Server->Frame();
	}

	void SR_SpawnServer(const char *levelname)
	{
		SR->Server->Spawn(levelname);
	}

	void SR_Restart()
	{
		SR->Server->Restart();
	}
}
