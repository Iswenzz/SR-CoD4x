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

		std::fill(this->FrameTimes.begin(), this->FrameTimes.end(), 0);
	}

	void Player::Spawn()
	{
		PMove->Initialize();
	}

	void Player::CalculateFrame(int time)
	{
		FrameTimes[FrameStackIndex++ % PLAYER_FPS_STACK] = time;
		cl->clFrames++;
	}

	void Player::CalculateFPS()
	{
		int i = 0;
		int maxOccurence = -1;
		int value = -1;

		int possibleValues[1000] = { 0 };
		for (i = 0; i < PLAYER_FPS_STACK; i++)
		{
			if (FrameTimes[i] <= 0 || FrameTimes[i] >= 1000)
				continue;
			possibleValues[FrameTimes[i]]++;
		}
		for (i = 0; i < 1000; i++)
		{
			if (possibleValues[i] == 0 || possibleValues[i] < maxOccurence)
				continue;
			maxOccurence = possibleValues[i];
			value = i;
		}
		if (value > 0)
			cl->clFPS = static_cast<int>(1000 / value);
		cl->clFrames = 0;
		FrameStackIndex = 0;
		std::fill(this->FrameTimes.begin(), this->FrameTimes.end(), 0);
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

		int time = cmd->serverTime - cl->lastUsercmd.serverTime;
		SR->Players[cl->gentity->client->ps.clientNum]->CalculateFrame(time);
	}
}
