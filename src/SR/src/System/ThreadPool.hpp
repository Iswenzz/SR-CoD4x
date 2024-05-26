#pragma once
#include "AsyncHandler.hpp"

namespace SR
{
	/// @brief Thread pool manager.
	class ThreadPool
	{
	public:
		static inline AsyncHandler Main;
		static inline AsyncHandler GSC;

		/// @brief Initialize the thread pool.
		static void Initialize();
	};
}
