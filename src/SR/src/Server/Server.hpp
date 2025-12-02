#pragma once
#include "Base.hpp"

namespace SR
{
	class Server
	{
	public:
		static void Spawn(const std::string& levelName);
		static void Restart();
		static void Frame();
	};
}
