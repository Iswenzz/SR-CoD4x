#pragma once
#include <iostream>
#include <string>

namespace SR
{
	enum class Channel
	{
		DEFAULT = 0x0,
		ERROR = 0x1,
		GAMENOTIFY = 0x2,
		BOLDGAME = 0x3,
		SUBTITLE = 0x4,
		OBITUARY = 0x5,
		LOGFILEONLY = 0x6,
		CONSOLEONLY = 0x7,
		GFX = 0x8,
		SOUND = 0x9,
		FILES = 0xA,
		DEVGUI = 0xB,
		PROFILE = 0xC,
		UI = 0xD,
		CLIENT = 0xE,
		SERVER = 0xF,
		SYSTEM = 0x10,
		PLAYERWEAP = 0x11,
		AI = 0x12,
		ANIM = 0x13,
		PHYS = 0x14,
		FX = 0x15,
		LEADERBOARDS = 0x16,
		LIVE = 0x17,
		PARSERSCRIPT = 0x18,
		SCRIPT = 0x19,
		SPAWNSYSTEM = 0x1A,
		COOPINFO = 0x1B,
		SERVERDEMO = 0x1C,
		DDL = 0x1D,
		NETWORK = 0x1E,
		SCHEDULER = 0x1F,
		TASK = 0x20,
		SPU = 0x21,
		FILEDL = 0x22,
		CVAR = 0x23,
		PLUGINS = 0x24,
		STEAM = 0x25,
		COUNT = 0x26
	};

	class Log
	{
	public:
		static void Write(Channel channel, const std::string& msg);
		static void Write(const std::string& fmt, ...);
		static void WriteLine(const std::string& fmt, ...);
	};
}
