#include "Debug.hpp"
#include "utils/Log.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void Debug::Initialize()
	{
		PacketSize = Cvar_RegisterBool("netchan_debug", qfalse, 0, "Debug the players packets.");
	}

	void Debug::NetchanPacketSize(int size)
	{
		if (!PacketSize->boolean)
			return;

		if (size >= 1050)
			Log::WriteLine("YELLOW: %d", size);
		else if (size >= 200)
			Log::WriteLine("PACKET: %d", size);
	}
}

C_EXTERN
{
	void NetchanDebugSize(int size)
	{
		Debug::NetchanPacketSize(size);
	}
}
