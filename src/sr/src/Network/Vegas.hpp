#pragma once
#include "Player/Player.hpp"

namespace SR
{
	class Vegas
	{
	public:
		static inline cvar_t *Enabled;
		static inline int ServiceID = 0;
		static inline hudelem_color_t Color = { 0 };
		static inline int Material = 0;

		static void Initialize();
		static void Shutdown();

		static qboolean Connect(netadr_t *from, msg_t *msg, int *connectionId);
		static void Disconnect(netadr_t *from, int connectionId);
		static int Message(netadr_t *from, msg_t *msg, int connectionId);

		static void Frame(const Ref<Player> &player);
	};
}
