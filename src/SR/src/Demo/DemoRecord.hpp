#pragma once
#include "Base.hpp"

namespace SR
{
	class DemoRecord
	{
	public:
		static void WriteSnapshot(client_t *client, msg_t *msg);
		static void BeginSnapshot(client_t *client, msg_t *msg);
		static void EndSnapshot(client_t *client, msg_t *msg);
		static void Frame(client_t *cl);
	};
}
