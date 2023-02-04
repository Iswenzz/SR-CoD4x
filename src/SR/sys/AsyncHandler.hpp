#pragma once
#include "Macros.hpp"

C_EXTERN
{
	#include <cgsc.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Async handler class.
	class AsyncHandler
	{
	public:
		async_handler *Handler;

		/// @brief Initialize the async handler.
		AsyncHandler();
		~AsyncHandler();

		/// @brief Create an async worker.
		/// @tparam T - The data type.
		/// @param data - The data.
		/// @param callback - The worker callback.
		/// @return
		template <typename T>
		async_worker* Worker(T* data, uv_work_cb callback)
		{
			return Worker(data, callback, nullptr);
		}

		/// @brief Create an async worker.
		/// @tparam T - The data type.
		/// @param data - The data.
		/// @param callback - The worker callback.
		/// @param afterCallback - The worker after callback.
		/// @return
		template <typename T>
		async_worker* Worker(T* data, uv_work_cb callback, uv_after_work_cb afterCallback)
		{
			return AsyncWorker(Handler, data, callback, afterCallback);
		}

		/// @brief Restart the async handler.
		void Restart();

		/// @brief Shutdown the async handler.
		void Shutdown();
	};
}
