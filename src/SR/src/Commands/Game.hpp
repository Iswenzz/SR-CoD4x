#pragma once
#include "Command.hpp"

namespace SR
{
	class GameCommands
	{
	public:
		static void Register();
		static void IsPrecached();
		static void LegacyWeapon();
		static void RadioPlay();
	};
}
