/*****************************************************************************
 * name:		be_interface.h
 *
 * desc:		botlib interface
 *
 *
 *****************************************************************************/

/*
"Do not go where the path leads, rather go where there's no track and leave a trail."

"AAS (Area Awareness System)"

"Part of the Gladiator is BoGuS (Bot Guidance System)"

"ANSI (Advanced Navigational System Interface)"

"to make things work the only thing you really have to do is think things work."

"a madman is just someone living in another reality which isn't shared among many people"
*/

// #define DEBUG			//debug code
#define RANDOMIZE // randomize bot behaviour
#if defined(WIN32) || defined(_WIN32)
	#define AASZIP // allow reading directly from aasX.zip files
#endif
#define QUAKE2 // bot for Quake2
// #define HALFLIFE		//bot for Half-Life

//
// global variable structures
//

// FIXME: get rid of this global structure
typedef struct botlib_globals_s
{
	int botlibsetup; // true when the bot library has been setup
	int maxentities; // maximum number of entities
	int maxclients;	 // maximum number of clients
	float time;		 // the global time
#ifdef DEBUG
	qboolean debug; // true if debug is on
	int goalareanum;
	vec3_t goalorigin;
	int runai;
#endif
} botlib_globals_t;

//
// global variables
//

extern botlib_globals_t botlibglobals;
extern botlib_import_t botimport;
extern int bot_developer; // true if developer is on

//
int Sys_MilliSeconds(void);
