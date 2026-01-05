#include "Netchan.hpp"
#include "Vegas.hpp"

#include "Player/Player.hpp"

namespace SR
{
	void Netchan::Initialize()
	{
		Vegas::Initialize();
	}

	void Netchan::Packet(netadr_t *from, client_t *cl, msg_t *msg)
	{
		if (!DEFINED_CLIENT(cl))
			return;

		auto player = Player::Get(cl->gentity->s.number);
		if (player)
			player->Packet(msg);
	}
}
