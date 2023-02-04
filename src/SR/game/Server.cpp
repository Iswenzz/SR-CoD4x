#include "Server.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
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

	void Server::Frame()
	{
		for (const auto &player : SR->Players)
		{
			if (player)
				player->Frame();
		}
		Voice->Frame();
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
}
