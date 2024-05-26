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

		/// @brief Initialize debug.
		static void Initialize();

		/// @brief Debug FPS.
		static void FPS();

		/// @brief Debug packet size.
		/// @param size - The packet size.
		static void NetchanPacketSize(int size);
	};
}
