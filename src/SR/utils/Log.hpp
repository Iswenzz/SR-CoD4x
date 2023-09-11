#pragma once

#include <iostream>
#include <string>

C_EXTERN
{
	#include <q_shared.h>
	#include <qcommon_logprint.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Log utility class.
	/// @remark No support for <format>.
	class Log
	{
	public:
		/// @brief Print a message.
		/// @param channel - The channel.
		/// @param msg - The message.
		static void Write(conChannel_t channel, std::string msg);

		/// @brief Write to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void Write(std::string fmt, ...);

		/// @brief Write a line to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void WriteLine(std::string fmt, ...);
	};
}
