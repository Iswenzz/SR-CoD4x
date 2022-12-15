#include "MP3.hpp"

#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION

#include <minimp3_ex.h>

namespace Iswenzz::CoD4x
{
	MP3::MP3(std::string filepath)
	{
		FilePath = filepath;
	}

	MP3::~MP3()
	{
		if (Input.is_open())
			Input.close();
		if (Output.is_open())
			Output.close();
	}
}
