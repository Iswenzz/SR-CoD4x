#pragma once
#include "Base.hpp"

#include <chrono>

namespace SR
{
	class Debug
	{
	public:
		static inline cvar_t *DebugFrameTime;
		static inline cvar_t *DebugPacketSize;

		static inline std::chrono::high_resolution_clock::time_point FrameTime{};
		static inline std::chrono::high_resolution_clock::time_point PreviousFrameTime{};

		static void Initialize();

		static void FPS();
		static void NetchanPacketSize(int size);
	};
}
