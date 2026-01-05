#include "Player.hpp"

namespace SR
{
	Player::Player(client_t *cl)
	{
		this->cl = cl;
		this->cl->clFrames = 0;
		this->ps = &cl->gentity->client->ps;

		std::fill(FrameTimes.begin(), FrameTimes.end(), 0);
	}

	void Player::Initialize()
	{
		Log::WriteLine("[Player] Connected {} {}", cl->gentity->s.number, cl->name);

		DemoPlayer = CreateScope<class DemoPlayer>(shared_from_this());
		PMove = CreateScope<class PMove>(shared_from_this());
	}

	void Player::Disconnect()
	{
		Log::WriteLine("[Player] Disconnected {} {}", cl->gentity->s.number, cl->name);
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
		if (!DEFINED_CLIENT(cl))
			return;

		CalculateFPS();
		VoiceChat();

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

	Ref<Player> &Player::Get(int num)
	{
		return List[num];
	}

	void Player::Add(client_t *cl)
	{
		Ref<Player> player = CreateRef<Player>(cl);
		player->Initialize();
		List[cl->gentity->s.number] = player;
	}
}
