#include "Vegas.hpp"

namespace Iswenzz::CoD4x
{
	Vegas::Vegas() : TCP(200)
	{
		NET_TCPAddEventType(SR_VegasMessage, SR_VegasConnect, SR_VegasDisconnect, ServiceID);
		IsEnabled = Cvar_RegisterBool("vegas", qfalse, 0, "Allow vegas rendering.");
	}

	bool Vegas::Connect(netadr_t *from, msg_t *msg)
	{
		return true;
	}

	void Vegas::Disconnect(netadr_t *from) { }

	int Vegas::Message(netadr_t *from, msg_t *msg)
	{
		MSG_BeginReading(msg);

		char id[30];
		char name[30];

		MSG_ReadString(msg, reinterpret_cast<char *>(&id), sizeof(id));
		MSG_ReadString(msg, reinterpret_cast<char *>(&name), sizeof(name));

		char r = 0;
		char g = 0;
		char b = 0;
		char a = 0;

		if (MSG_ReadByte(msg))
		{
			r = MSG_ReadByte(msg);
			g = MSG_ReadByte(msg);
			b = MSG_ReadByte(msg);
			a = MSG_ReadByte(msg);
		}

		Color.split = { r, g, b, a };
		Material = G_FindMaterial(name);
		return 0;
	}

	void Vegas::Frame(Player *player)
	{
		if (!IsEnabled->boolean)
			return;

		clientSnapshot_t *frame = player->GetFrame();

		frame->ps.hud.current[0].color = Color;
		frame->ps.hud.current[0].materialIndex = Material;
	}
}
