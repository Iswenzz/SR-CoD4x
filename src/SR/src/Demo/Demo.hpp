#pragma once
#include "Base.hpp"

// clang-format off
#include <CoD4DM1/Demo/Demo.hpp>
#include <CoD4DM1/API/DemoReader.hpp>
// clang-format on

#include <filesystem>

#define DEMO_MAX_CONFIGSTRINGS 2 * 2442

namespace SR
{
	/// @brief Demo frame.
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
		IZ_ASYNC(OpenAsync)
	public:
		std::string ID;
		Scope<CoD4::DM1::DemoReader> Reader;
		std::vector<DemoFrame> Frames{};
		std::array<std::string, DEMO_MAX_CONFIGSTRINGS> ConfigStrings{};
		std::vector<std::string> Weapons{};

		std::string MapName;
		std::string PlayerName;

		int Version = 0;
		int LastValidFrame = 0;
		bool HasReadInformations = false;
		bool IsLoaded = false;

		/// @brief Initialize a new Demo.
		/// @param id - The demo id.
		/// @param path - The demo path.
		Demo(const std::string& id, const std::string& path);
		~Demo();

		/// @brief Open a demo.
		void Open();

		/// @brief Read the demo information.
		void ReadDemoInformations();

		/// @brief Interpolate invalid packets.
		/// @param interpolateFrame - The last valid frame to interpolate the previous invalid frames.
		void Interpolate(DemoFrame& interpolateFrame);

		/// @brief Get the demo version.
		void GetVersion();

		/// @brief Get the player velocity.
		/// @param frame - The current frame.
		/// @return
		int GetVelocity(DemoFrame& frame);

		/// @brief Process chat messages.
		/// @return
		std::vector<std::string> ProcessChat();

		/// @brief Can parse the snapshot.
		/// @return
		bool CanParseSnapshot();
	};
}
