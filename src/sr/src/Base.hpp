#pragma once

#include "Macros.hpp"
#include "System/Async.hpp"
#include "Utils/Log.hpp"
#include "Utils/Ref.hpp"

#include <array>
#include <map>
#include <unordered_map>
#include <vector>

IZ_C
{
	// clang-format off
	#include <cscr_variable.h>
	#include <cscr_stringlist.h>
	#include <g_shared.h>
	#include <huffman.h>
	#include <net_game.h>
	#include <qcommon_logprint.h>
	#include <scr_vm.h>
	#include <server.h>
	#include <sv_snapshot.h>
	#include <sys_main.h>
	#include <xassets.h>
	// clang-format on
}
// clang-format off
namespace SR { };
using namespace SR;
// clang-format on
