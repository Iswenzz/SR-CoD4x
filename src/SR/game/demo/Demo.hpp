#pragma once
#include "Macros.hpp"

#include <CoD4DM1/API/DemoReader.hpp>
#include <CoD4DM1/Crypt/Huffman.hpp>
#include <memory>
#include <map>

C_EXTERN
{
	#include <cgsc.h>
	#include <server.h>
	#include <q_math.h>
}

namespace Iswenzz::CoD4x
{
	struct DemoFrame
	{
		playerState_t ps;
		int time;
		int fps;
		std::string playerName;
		std::vector<std::string> chat;
		std::map<int, entityState_t> entities;
		char forwardmove;
		char rightmove;
		int buttons;
	};

	/// @brief Game demo.
	class Demo
	{
	public:
		std::string ID;
		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;
		std::vector<DemoFrame> Frames{ };
		std::array<std::string, MAX_CONFIGSTRINGS + 1> ConfigStrings{ };
		std::vector<std::string> Weapons{ };
		bool IsLoading = false;

		/// @brief Initialize a new Demo.
		/// @param id - The demo id.
		/// @param path - The demo path.
		Demo(std::string id, std::string path);
		~Demo();

		/// @brief Initialize the demo huffman and mutex.
		static void Initialize();

		/// @brief Open a demo.
		/// @param req - The worker request.
		static void Open(uv_work_t *req);

		/// @brief Process chat messages.
		/// @return
		std::vector<std::string> ProcessChat();

	private:
		inline static uv_mutex_t Mutex;
	};
}
