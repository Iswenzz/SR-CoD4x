#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Game::Game()
	{
		Log::WriteLine("[SR] Initialize");

		Environment::Build();
		Demo::Initialize();

		Server = std::make_unique<class Server>();
		Netchan = std::make_unique<class Netchan>();
		DemoContainer = std::make_unique<class DemoContainer>();

		CommandsContainer::Register();
		Debug::Initialize();
	}

	Game::~Game()
	{
		Log::WriteLine("[SR] Shutdown");

		AsyncShutdown();
	}
}

Game *SR;

C_EXTERN void SR_Initialize()
{
	SR = new Game();
}

C_EXTERN void SR_Shutdown()
{
	SR->~Game();
}
