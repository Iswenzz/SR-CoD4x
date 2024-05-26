#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Process network messages.
	class Netchan
	{
	public:
		/// @brief Initialize netchan.
		static void Initialize();

		/// @brief Received packet.
		/// @param from - The address.
		/// @param cl - The client.
		/// @param msg - The packet message.
		static void Packet(netadr_t *from, client_t *cl, msg_t *msg);
	};
}
