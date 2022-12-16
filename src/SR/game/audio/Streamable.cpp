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

	std::vector<short> Streamable::Play()
	{
		return { };
	}
}
