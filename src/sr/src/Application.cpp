#include "Application.hpp"

#include "Audio/Speex.hpp"
#include "Commands/Container.hpp"
#include "Demo/DemoContainer.hpp"
#include "Network/Netchan.hpp"
#include "System/Debug.hpp"
#include "System/Environment.hpp"

namespace SR
{
	void Application::Start()
	{
		Log::WriteLine("^5[SR] Start");
		Environment::Build();

		Netchan::Initialize();
		Speex::Initialize();
		DemoContainer::Initialize();
		CommandsContainer::Initialize();
		Debug::Initialize();
	}

	void Application::Shutdown()
	{
		Log::WriteLine("^5[SR] Shutdown");

		Speex::Shutdown();
	}
}
