#include "ThreadPool.hpp"

namespace SR
{
	void ThreadPool::Initialize()
	{
		Main.Restart();
		GSC.Restart();
	}
}
