#include "ThreadPool.hpp"

namespace Iswenzz::CoD4
{
	AsyncHandler::AsyncHandler()
	{
		Handler = AsyncInit();
	}

	AsyncHandler::~AsyncHandler()
	{
		Shutdown();
	}

	void AsyncHandler::Restart()
	{
		Shutdown();
		Handler = AsyncInit();
	}

	void AsyncHandler::Shutdown()
	{
		AsyncShutdown(Handler);
	}
}
