#include "Demo.hpp"
#include "utils/Utils.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo(std::string id, std::string path)
	{
		ID = id;
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>(path);

		AsyncCall(this, Open, nullptr);
	}

	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Initialize()
	{
		Iswenzz::CoD4::DM1::Huffman::InitMain();
		uv_mutex_init(&Demo::Mutex);
	}

	void Demo::Open(uv_work_t* req)
	{
		uv_mutex_lock(&Demo::Mutex);

		Demo *demo = (Demo *)req->data;
		demo->IsLoading = true;

		try
		{
			DemoFrame previousFrame = { 0 };

			while (demo->Reader->Next())
			{
				DemoFrame frame = { 0 };

				if (demo->Reader->DemoFile->CurrentMessageType == Iswenzz::CoD4::DM1::MSGType::MSG_FRAME)
					continue;
				if (!demo->Reader->GetCurrentSnapshot().valid)
					continue;

				auto ps = demo->Reader->GetCurrentSnapshot().ps;
				auto archive = demo->Reader->GetCurrentFrame();

				frame.chat = demo->ProcessChat();
				frame.time = demo->Reader->GetTimeMilliseconds();
				frame.fps = demo->Reader->GetFPS();
				frame.ps = *reinterpret_cast<playerState_t *>(&ps);
				frame.playerName = demo->Reader->GetPlayerName().netname;
				frame.entities = previousFrame.entities;
				frame.forwardmove = *(char *)&ps.dofNearStart;
				frame.rightmove = *(char *)&ps.dofNearEnd;
				frame.buttons = *(int *)&ps.dofFarStart;

				for (auto &ent : demo->Reader->GetLastUpdatedEntities())
				{
					if (ent.eType == ET_SCRIPTMOVER)
						frame.entities[ent.number] = *reinterpret_cast<entityState_t*>(&ent);
				}

				previousFrame = frame;
				demo->Frames.push_back(frame);
			}

			demo->ConfigStrings = demo->Reader->DemoFile->ConfigStrings;
			demo->Weapons = Utils::SplitString(demo->Reader->GetConfigString("defaultweapon_mp"), ' ');
		}
		catch (...) { }

		demo->Reader->Close();
		demo->IsLoading = false;
		uv_mutex_unlock(&Demo::Mutex);
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
