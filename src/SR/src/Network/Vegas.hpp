#pragma once
#include "Player/Player.hpp"

namespace SR
{
	/// @brief TCP link betweeen Vegas and the server.
	class Vegas
	{
	public:
		static inline cvar_t *Enabled;
		static inline int ServiceID = 0;
		static inline hudelem_color_t Color = { 0 };
		static inline int Material = 0;

		/// @brief Initialize vegas server.
		static void Initialize();

		/// @brief Shutdown vegas server.
		static void Shutdown();

		/// @brief User connection.
		/// @param from - The address.
		/// @param msg - The message.
		/// @param connectionId - The connection id.
		/// @return bool
		static bool Connect(netadr_t *from, msg_t *msg, int *connectionId);

		/// @brief Disconnect user.
		/// @param from - The address.
		/// @param connectionId - The connection id.
		static void Disconnect(netadr_t *from, int connectionId);

		/// @brief Received message.
		/// @param from - The address.
		/// @param msg - The message.
		/// @param connectionId - The connection id.
		/// @return int
		static int Message(netadr_t *from, msg_t *msg, int connectionId);

		/// @brief Render vegas to the player.
		/// @param player - The player.
		static void Frame(const Ref<Player> &player);
	};
}
