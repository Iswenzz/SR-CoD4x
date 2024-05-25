#include "ThreadPool.hpp"

namespace Iswenzz::CoD4
{
	ThreadPool::ThreadPool()
	{
		Main = std::make_unique<AsyncHandler>();
		GSC = std::make_unique<AsyncHandler>();
	}
}
