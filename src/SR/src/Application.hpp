#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Game server.
	class Application
	{
	public:
		/// @brief Start the application.
		static void Start();

		/// @brief Shutdown the application.
		static void Shutdown();
	};
}
