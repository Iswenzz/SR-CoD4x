#pragma once
#include <CoD4DM1/API/DemoReader.hpp>
#include <CoD4DM1/Crypt/Huffman.hpp>
#include <cgsc.h>

#include <map>
#include <server.h>
#include <q_math.h>

namespace Iswenzz::CoD4x
{
	struct DemoFrame
	{
		bool valid;
		playerState_t ps;
		int time;
		int fps;
		std::string playerName;
		std::vector<std::string> chat;
		std::map<int, entityState_t> entities;
		int velocity;
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
		std::array<std::string, MAX_CONFIGSTRINGS> ConfigStrings{ };
		std::vector<std::string> Weapons{ };

		std::string MapName;
		std::string PlayerName;

		int Version = 0;
		int LastValidFrame = 0;
		bool HasReadInformations = false;
		bool IsLoaded = false;

		/// @brief Initialize a new Demo.
		/// @param id - The demo id.
		/// @param path - The demo path.
		Demo(std::string id, std::string path);
		~Demo();

		/// @brief Initialize the demo huffman and mutex.
		static void Initialize();

		/// @brief Open a demo.
		void Open();

		/// @brief Open a demo async.
		/// @param req - The worker request.
		static void OpenAsync(uv_work_t *req);

		/// @brief Read the demo information.
		void ReadDemoInformations();

		/// @brief Interpolate invalid packets.
		/// @param interpolateFrame - The last valid frame to interpolate the previous invalid frames.
		void Interpolate(DemoFrame &interpolateFrame);

		/// @brief Get the demo version.
		void GetVersion();

		/// @brief Get the player velocity.
		/// @param frame - The current frame.
		/// @return
		int GetVelocity(DemoFrame &frame);

		/// @brief Process chat messages.
		/// @return
		std::vector<std::string> ProcessChat();

		/// @brief Can parse the snapshot.
		/// @return
		bool CanParseSnapshot();

	private:
		static inline uv_mutex_t Mutex;
	};
}
