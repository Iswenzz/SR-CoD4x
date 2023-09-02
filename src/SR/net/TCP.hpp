#pragma once
#include <string>
#include <memory>
#include <msg.h>
#include <net_game.h>

namespace Iswenzz::CoD4x
{
	class TCP
	{
	public:
		int ServiceID = 0;

		/// @brief Initialize a new TCP service.
		/// @param serviceId - The service ID.
		TCP(int serviceId);
		virtual ~TCP() = default;

		/// @brief User connection.
		/// @param from - The address.
		/// @param msg - The message.
		/// @return bool
		virtual bool Connect(netadr_t *from, msg_t *msg) = 0;

		/// @brief Disconnect user.
		/// @param from - The address.
		virtual void Disconnect(netadr_t *from) = 0;

		/// @brief Received message.
		/// @param from - The address.
		/// @param msg - The message.
		/// @return int
		virtual int Message(netadr_t *from, msg_t *msg) = 0;
	};
}
