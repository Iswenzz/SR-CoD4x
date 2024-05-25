#include "Debug.hpp"

#include "Utils/Log.hpp"

#include <chrono>

namespace Iswenzz::CoD4x
{
	void Debug::Initialize()
	{
		DebugFrameTime = Cvar_RegisterBool("debug_fps", qfalse, 0, "Debug the server FPS");
		DebugPacketSize = Cvar_RegisterBool("debug_netchan", qfalse, 0, "Debug the players packets");
	}

	void Debug::FPS()
	{
		if (!DebugFrameTime->boolean)
			return;

		FrameTime = std::chrono::high_resolution_clock::now();

		double duration = std::chrono::duration<double, std::milli>(FrameTime - PreviousFrameTime).count();
		int fps = 0;
		if (duration > 0)
			fps = 1000 / duration;
		if (fps > 0)
			Log::WriteLine("[Debug] FPS %d", fps);

		PreviousFrameTime = FrameTime;
	}

	void Debug::NetchanPacketSize(int size)
	{
		if (!DebugPacketSize->boolean)
			return;

		if (size >= 1050)
			Log::WriteLine("^3[Debug] Packet %d", size);
		else if (size >= 200)
			Log::WriteLine("^2[Debug] Packet %d", size);
	}
}
