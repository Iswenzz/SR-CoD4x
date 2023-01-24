#pragma once
#include "PMove.hpp"
#include "game/demo/DemoPlayer.hpp"

#define PMF_PRONING 0x1
#define PMF_CROUCHING 0x2

C_EXTERN
{
	#include <server.h>
}

#define IsDefinedClient(cl) 		(cl && cl->gentity && cl->gentity->client)
#define IsDefinedClientNum(num) 	(SR->Players[num] && SR->Players[num]->cl->gentity && SR->Players[num]->cl->gentity->client)
#define IsDefinedGClient(client) 	(client)

namespace Iswenzz::CoD4x
{
	/// @brief Player class.
	class Player
	{
	public:
		client_t* cl;
		playerState_t* ps;

		std::unique_ptr<PMove> PMove;
		std::unique_ptr<DemoPlayer> DemoPlayer;

		int CurrentFrameTime = 0;
		int PreviousFrameTime = 0;
		std::vector<int> FrameTimes{ };

		int FPS = 0;
		int SurfaceFlags = 0;

		bool Voice = false;
		int VoiceCount = 0;
		int VoiceTime = 0;
		int LastVoiceTime = 0;

		bool ProximityEnabled = false;
		bool RadioEnabled = false;

		/// @brief Initialize a new player.
		/// @param cl - The client.
		Player(client_t *cl);
		~Player() = default;

		/// @brief Player spawn.
		void Spawn();

		/// @brief Calculate the player Frame.
		/// @param time - The frame time.
		void CalculateFrame(int time);

		/// @brief Calculate the player FPS.
		void CalculateFPS();

		/// @brief Player packet.
		/// @param msg - The packet message.
		void Packet(msg_t *msg);

		/// @brief Player render frame.
		void Frame();

		/// @brief Process player voice chat.
		void VoiceChat();

		/// @brief Get the last player frame.
		/// @return clientSnapshot_t*
		clientSnapshot_t *GetFrame();

		/// @brief Get a player.
		/// @param num - The player num.
		static std::shared_ptr<Player> Get(int num);
	};
}
