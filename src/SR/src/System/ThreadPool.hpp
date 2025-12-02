#pragma once
#include "AsyncHandler.hpp"

namespace SR
{
	class ThreadPool
	{
	public:
		static inline AsyncHandler Main;
		static inline AsyncHandler GSC;

		static void Initialize();
	};
}
