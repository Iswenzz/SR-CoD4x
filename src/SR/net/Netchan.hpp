#pragma once
#include "Macros.hpp"

C_EXTERN
{
	#include <netchan.h>
	#include <server.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Process network messages.
	class Netchan
	{
	public:
		/// @brief Initialize the network.
		Netchan() = default;
		~Netchan() = default;

		/// @brief Received packet.
		/// @param from - The address.
		/// @param cl - The client.
		/// @param msg - The packet message.
		void Packet(netadr_t *from, client_t* cl, msg_t *msg);
	};
}
