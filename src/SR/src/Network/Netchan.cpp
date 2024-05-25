#include "Netchan.hpp"

#include "Player/Player.hpp"

namespace Iswenzz::CoD4x
{
	void Netchan::Packet(netadr_t *from, client_t *cl, msg_t *msg)
	{
		if (!IsDefinedClient(cl))
			return;

		auto player = Player::Get(cl->gentity->s.number);
		if (player)
			player->Packet(msg);
	}
}
