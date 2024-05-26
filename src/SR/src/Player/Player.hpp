#pragma once
#include "Demo/DemoPlayer.hpp"
#include "PMove.hpp"

#define PLAYER_FPS_STACK 20
#define PMF_PRONING 0x1
#define PMF_CROUCHING 0x2

namespace SR
{
	/// @brief Player class.
	/// @remarks cl->gentity->s.number is the client number.
	/// @remarks cl->gentity->client->ps.clientNumber is the spectator client or client if not spectating.
	class Player : public std::enable_shared_from_this<Player>
	{
	public:
		static inline std::array<Ref<Player>, MAX_CLIENTS> List{};

		client_t *cl = nullptr;
		playerState_t *ps = nullptr;
		Scope<class PMove> PMove;
		Scope<class DemoPlayer> DemoPlayer;
		int SurfaceFlags = 0;

		int FPS = 0;
		int FrameStackIndex = 0;
		std::array<int, PLAYER_FPS_STACK> FrameTimes{};

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

		/// @brief Initialize the player.
		void Initialize();

		/// @brief Player disconnect.
		void Disconnect();

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
		static Ref<Player> &Get(int num);

		/// @brief Add a new player.
		/// @param cl - The client.
		static void Add(client_t *cl);
	};
}
