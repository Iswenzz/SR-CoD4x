#pragma once
#include "AsyncHandler.hpp"

#include <memory>

namespace Iswenzz::CoD4x
{
	/// @brief Thread pool manager.
	class ThreadPool
	{
	public:
		std::unique_ptr<AsyncHandler> Main;
		std::unique_ptr<AsyncHandler> GSC;

		/// @brief Initialize the thread pool.
		ThreadPool();
		~ThreadPool() = default;
	};
}
