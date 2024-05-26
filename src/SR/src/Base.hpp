#pragma once

#include "Macros/Base.hpp"
#include "Utils/Log.hpp"
#include "Utils/Ref.hpp"

#include <array>
#include <map>
#include <vector>

IZ_C
{
	// clang-format off
	#include <CGSC/cgsc.h>
	#include <server.h>
	#include <net_game.h>
	#include <sys_main.h>
	#include <huffman.h>
	#include <sv_snapshot.h>
	#include <qcommon_logprint.h>
	// clang-format on
}
// clang-format off
namespace SR { };
using namespace SR;
// clang-format on
