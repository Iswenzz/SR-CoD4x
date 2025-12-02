#pragma once
#include "Demo.hpp"
#include "Player/Player.hpp"

namespace SR
{
	class DemoPlayer
	{
	public:
		Ref<class Demo> Demo;
		Ref<class Player> Player;
		gentity_t* Entity = nullptr;
		int Velocity = 0;
		std::string Weapon = "";
		DemoFrame CurrentFrame;
		int FrameIndex = 0;
		int PreviousFrameIndex = 0;
		bool Slowmo = false;
		int SlowmoIndex = 0;
		int SlowmoThreshold = 0;

		DemoPlayer(const Ref<class Player>& player);
		~DemoPlayer() = default;

		void Play(const Ref<class Demo>& demo);
		void Stop();

		void UpdateEntity(snapshotInfo_t* snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to,
			qboolean force);
		bool ComputeFrame();
		void ComputeSlowmotion(DemoFrame& frame);

		void Packet();
		void Frame();
	};
}
