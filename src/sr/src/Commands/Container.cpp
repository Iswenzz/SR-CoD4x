#include "Container.hpp"

#include "Debug.hpp"
#include "Demo.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace SR
{
	void CommandsContainer::Initialize()
	{
		DebugCommands::Register();
		DemoCommands::Register();
		EntityCommands::Register();
		PlayerCommands::Register();
		GameCommands::Register();
	}
}
