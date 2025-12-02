#pragma once
#include "Base.hpp"

namespace SR
{
	class AsyncHandler
	{
	public:
		async_handler *Handler = nullptr;

		AsyncHandler();
		~AsyncHandler();

		void Restart();

		template <typename T>
		async_worker *Worker(T *data, uv_work_cb callback)
		{
			return Worker(data, callback, nullptr);
		}

		template <typename T>
		async_worker *Worker(T *data, uv_work_cb callback, uv_after_work_cb afterCallback)
		{
			return AsyncWorker(Handler, data, callback, afterCallback);
		}
	};
}
