#pragma once
#include <sv_snapshot.h>
#include <huffman.h>

namespace Iswenzz::CoD4x
{
	/// @brief Demo recording.
	class DemoRecord
	{
	public:
		/// @brief Write a demo snapshot.
		/// @param client - The client.
		/// @param msg - The demo message.
		static void WriteSnapshot(client_t *client, msg_t *msg);

		/// @brief Begin a demo snapshot.
		/// @param client - The client.
		/// @param msg - The demo message.
		static void BeginSnapshot(client_t *client, msg_t *msg);

		/// @brief End a demo snapshot.
		/// @param client - The client.
		/// @param msg - The demo message.
		static void EndSnapshot(client_t *client, msg_t *msg);

		/// @brief Demo recording frame.
		/// @param cl - The client.
		static void Frame(client_t *cl);
	};
}
