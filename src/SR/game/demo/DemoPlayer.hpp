#pragma once
#include "Demo.hpp"

namespace Iswenzz::CoD4x
{
	class Player;

	/// @brief Play a demo on a player.
	class DemoPlayer
	{
	public:
		std::shared_ptr<Demo> Demo;

		Player *Player;
		gentity_t *Entity;
		DemoFrame CurrentFrame;

		int StartTime = 0;
		int FrameIndex = 0;
		int PreviousFrameIndex = 0;

		bool Slowmo = false;
		int SlowmoIndex = 0;
		int SlowmoThreshold = 0;

		int Velocity = 0;
		std::string Weapon = "";

		/// @brief Initialize the DemoPlayer.
		/// @param player - The player.
		DemoPlayer(class Player *player);
		~DemoPlayer() = default;

		/// @brief Play a demo on a player.
		/// @param demo - The demo.
		void Play(const std::shared_ptr<class Demo>& demo);

		/// @brief Stop the demo.
		void Stop();

		/// @brief Update entities.
		/// @param snapInfo - The snap info.
		/// @param msg - The frame message.
		/// @param time - The frame time.
		/// @param from - From entity.
		/// @param to - To entity.
		/// @param force - Force fields.
		void UpdateEntity(snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force);

		/// @brief Compute the current demo frame.
		bool ComputeFrame();

		/// @brief Process the slowmotion.
		/// @param frame - The demo frame.
		void ComputeSlowmotion(DemoFrame &frame);

		/// @brief Demo player packet.
		void Packet();

		/// @brief Demo player frame.
		void Frame();
	};
}
