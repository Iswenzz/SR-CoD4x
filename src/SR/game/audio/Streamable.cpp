#include "Streamable.hpp"

namespace Iswenzz::CoD4x
{
	Streamable::~Streamable()
	{
		if (Input.is_open())
			Input.close();
		if (Output.is_open())
			Output.close();
	}

	void Streamable::ProcessPackets()
	{
		int position = 0;
		bool lastFrame = false;

		while (!lastFrame)
		{
			lastFrame = position + SPEEX_FRAME_SIZE >= Buffer.size();
			int size = lastFrame ? Buffer.size() - position : SPEEX_FRAME_SIZE;
			std::vector<short> stream(size);

			auto start = Buffer.begin() + position;
			auto end = start + stream.size();
			std::copy(start, end, stream.begin());
			stream.resize(SPEEX_FRAME_SIZE);

			position += stream.size();
			VoicePacket_t packet = Speex::Encode(stream);
			StreamPackets.push_back(packet);
		}
	}

	VoicePacket_t Streamable::Play()
	{
		return StreamPackets[StreamPosition++];
	}

	bool Streamable::IsStreamEnd()
	{
		return StreamPosition >= StreamPackets.size();
	}
}
