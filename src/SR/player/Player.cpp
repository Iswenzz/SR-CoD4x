#include "Player.hpp"
#include "SR.hpp"
#include "utils/Utils.hpp"
#include "utils/Log.hpp"

namespace Iswenzz::CoD4x
{
	Player::Player(client_t *cl)
	{
		this->cl = cl;
		this->cl->clFrames = 0;
		this->ps = &cl->gentity->client->ps;

		this->DemoPlayer = std::make_unique<class DemoPlayer>(this);
		this->PMove = std::make_unique<class PMove>(this);
	}

	void Player::Spawn()
	{
		PMove->Initialize();
	}

	void Player::CalculateFrame(int time)
	{
		if (time > CurrentFrameTime)
		{
			PreviousFrameTime = CurrentFrameTime;
			CurrentFrameTime = time;
			FrameTimes.push_back(1000 / (CurrentFrameTime - PreviousFrameTime));
		}
	}

	void Player::CalculateFPS()
	{
		if (FrameTimes.empty())
			return;

		FPS = Utils::VectorAverageMode(FrameTimes);
		FrameTimes.clear();

		cl->clFPS = FPS;
		cl->clFrames = 0;
	}

	void Player::Packet(msg_t *msg)
	{
		DemoPlayer->Packet();
	}

	void Player::Frame()
	{
		if (!IsDefinedClient(cl))
			return;

		CalculateFPS();
		VoiceChat();

		SR->Server->Vegas->Frame(this);
		DemoPlayer->Frame();
	}

	void Player::VoiceChat()
	{
		LastVoiceTime = VoiceTime;
		VoiceTime = cl->gentity->client->lastVoiceTime;

		if (VoiceTime != LastVoiceTime)
		{
			Voice = true;
			VoiceCount = 0;
		}
		else if (Voice)
		{
			VoiceCount++;
			if (VoiceCount > 5)
			{
				Voice = false;
				VoiceCount = 0;
			}
		}
	}

	clientSnapshot_t *Player::GetFrame()
	{
		return &cl->frames[cl->netchan.outgoingSequence & PACKET_MASK];
	}

	std::shared_ptr<Player> Player::Get(int num)
	{
		return IsDefinedClientNum(num) ? SR->Players[num] : nullptr;
	}
}

C_EXTERN
{
	void SR_InitializePlayer(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return;

		Log::WriteLine("[Player] Connected %d %s", cl->gentity->s.number, cl->name);
		SR->Players[cl->gentity->s.number] = std::make_shared<Player>(cl);
	}

	void SR_FreePlayer(client_t *cl)
	{
		if (!IsDefinedClient(cl))
			return;

		Log::WriteLine("[Player] Disconnected %d %s", cl->gentity->client->ps.clientNum, cl->name);
	}

	void SR_ClientSpawn(gclient_t *client)
	{
		if (!IsDefinedGClient(client))
			return;

		SR->Players[client->ps.clientNum]->Spawn();
	}

	void SR_CalculateFrame(client_t *cl, usercmd_t *cmd)
	{
		if (!IsDefinedClient(cl))
			return;

		SR->Players[cl->gentity->client->ps.clientNum]->CalculateFrame(cl->gentity->client->ps.commandTime);
	}
}
