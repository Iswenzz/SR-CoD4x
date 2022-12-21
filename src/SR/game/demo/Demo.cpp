#include "Demo.hpp"
#include "utils/Utils.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo(std::string id, std::string path)
	{
		ID = id;
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>(path);

		AsyncCall(this, OpenAsync, &AsyncNull);
	}

	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Initialize()
	{
		Iswenzz::CoD4::DM1::Huffman::InitMain();
		uv_mutex_init(&Mutex);
	}

	void Demo::Open()
	{
		IsLoaded = false;
		DemoFrame previousFrame = { 0 };
		previousFrame.valid = true;

		try
		{
			while (Reader->Next())
			{
				DemoFrame frame = { 0 };

				if (Reader->DemoFile->CurrentMessageType == Iswenzz::CoD4::DM1::MSGType::MSG_FRAME)
					continue;

				auto ps = Reader->GetCurrentSnapshot().ps;
				auto archive = Reader->GetCurrentFrame();

				frame.valid = Reader->GetCurrentSnapshot().valid;
				frame.chat = ProcessChat();
				frame.time = Reader->GetTimeMilliseconds();
				frame.fps = Reader->GetFPS();
				frame.ps = *reinterpret_cast<playerState_t *>(&ps);
				frame.playerName = Reader->GetPlayerName().netname;
				frame.entities = previousFrame.entities;
				frame.forwardmove = *(char *)&ps.dofNearStart;
				frame.rightmove = *(char *)&ps.dofNearEnd;
				frame.buttons = *(int *)&ps.dofFarStart;

				// Entities
				for (auto &ent : Reader->GetLastUpdatedEntities())
				{
					if (ent.eType == ET_SCRIPTMOVER)
						frame.entities[ent.number] = *reinterpret_cast<entityState_t*>(&ent);
				}

				// Interpolate invalid packets
				if (frame.valid)
				{
					if (!previousFrame.valid)
						Interpolate(frame);
					LastValidFrame = Frames.size();
				}

				previousFrame = frame;
				Frames.push_back(frame);
			}

			ConfigStrings = Reader->DemoFile->ConfigStrings;
			Weapons = Utils::SplitString(Reader->GetConfigString("defaultweapon_mp"), ' ');
		}
		catch (...) { }

		Reader->Close();
		IsLoaded = true;
	}

	void Demo::OpenAsync(uv_work_t *req)
	{
		uv_mutex_lock(&Mutex);

		Demo *demo = reinterpret_cast<Demo*>(req->data);
		demo->Open();

		uv_mutex_unlock(&Mutex);
	}

	void Demo::Interpolate(DemoFrame &interpolateFrame)
	{
		DemoFrame *validFrame = &Frames[LastValidFrame];

		for (int i = LastValidFrame + 1, c = 1; i < Frames.size(); i++, c++)
		{
			DemoFrame *frame = &Frames[i];
			float interpolate = static_cast<float>(c) / (Frames.size() - LastValidFrame);

			frame->entities = interpolateFrame.entities;
			frame->ps = interpolateFrame.ps;
			frame->buttons = interpolateFrame.buttons;
			frame->ps.commandTime = std::lerp(validFrame->ps.commandTime, interpolateFrame.ps.commandTime, interpolate);

			frame->ps.origin[0] = std::lerp(validFrame->ps.origin[0], interpolateFrame.ps.origin[0], interpolate);
			frame->ps.origin[1] = std::lerp(validFrame->ps.origin[1], interpolateFrame.ps.origin[1], interpolate);
			frame->ps.origin[2] = std::lerp(validFrame->ps.origin[2], interpolateFrame.ps.origin[2], interpolate);

			frame->ps.velocity[0] = std::lerp(validFrame->ps.velocity[0], interpolateFrame.ps.velocity[0], interpolate);
			frame->ps.velocity[1] = std::lerp(validFrame->ps.velocity[1], interpolateFrame.ps.velocity[1], interpolate);
			frame->ps.velocity[2] = std::lerp(validFrame->ps.velocity[2], interpolateFrame.ps.velocity[2], interpolate);

			// Prevent angle clamp interpolation
			if (std::abs(validFrame->ps.viewangles[0] - interpolateFrame.ps.viewangles[0]) < 170)
				frame->ps.viewangles[0] = std::lerp(validFrame->ps.viewangles[0], interpolateFrame.ps.viewangles[0], interpolate);
			if (std::abs(validFrame->ps.viewangles[1] - interpolateFrame.ps.viewangles[1]) < 170)
				frame->ps.viewangles[1] = std::lerp(validFrame->ps.viewangles[1], interpolateFrame.ps.viewangles[1], interpolate);
			if (std::abs(validFrame->ps.viewangles[2] - interpolateFrame.ps.viewangles[2]) < 170)
				frame->ps.viewangles[2] = std::lerp(validFrame->ps.viewangles[2], interpolateFrame.ps.viewangles[2], interpolate);
		}
	}

	std::vector<std::string> Demo::ProcessChat()
	{
		std::vector<std::string> chat;
		std::vector<std::string> commands = Reader->GetLastCommandStrings();

		for (const std::string& command : commands)
		{
			if (command[0] == 'h')
				chat.push_back(command.substr(3, command.size() - 4));
		}
		return chat;
	}
}
