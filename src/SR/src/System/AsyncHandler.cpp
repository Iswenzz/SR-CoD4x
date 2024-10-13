#include "ThreadPool.hpp"

namespace SR
{
	AsyncHandler::AsyncHandler()
	{
		Handler = AsyncInit();
	}

	AsyncHandler::~AsyncHandler()
	{
		if (Handler)
			AsyncShutdown(Handler);
	}

	void AsyncHandler::Restart()
	{
		if (Handler)
			AsyncShutdown(Handler);
		Handler = AsyncInit();
	}
}
