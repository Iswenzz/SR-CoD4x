#pragma once
#include "Base.hpp"

namespace SR
{
	class Netchan
	{
	public:
		static void Initialize();
		static void Packet(netadr_t *from, client_t *cl, msg_t *msg);
	};
}
