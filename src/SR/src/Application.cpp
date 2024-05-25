#include "Application.hpp"

namespace Iswenzz::CoD4x
{
	Application::Application()
	{
		Log::WriteLine("[SR] Initialize");

		Environment::Build();
		Speex::Initialize();
		Demo::Initialize();

		Server = std::make_unique<class Server>();
		Netchan = std::make_unique<class Netchan>();
		DemoContainer = std::make_unique<class DemoContainer>();
		ThreadPool = std::make_unique<class ThreadPool>();

		CommandsContainer::Register();
		Debug::Initialize();
	}

	Application::~Application()
	{
		Log::WriteLine("[SR] Shutdown");

		Speex::Shutdown();
	}
}

Application *SR;
