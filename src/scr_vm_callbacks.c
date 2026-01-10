#include "q_shared.h"
#include "entity.h"
#include "scr_vm.h"

// Only CoD4 gamescript callback functions here

/*

qboolean Scr_PlayerSay(gentity_t* from, int mode, const char* text){

	int callback;
	int threadId;
	int i, j;

	char textbuf[MAX_STRING_CHARS];
	for(i = 0, j = 0; i < sizeof(textbuf) -1 && text[i]; ++i)
	{
		textbuf[j] = text[i];

		if(textbuf[j] < ' ')
		{
			continue;
		}
		++j;
	}
	textbuf[j] = '\0';

	callback = script_CallBacks_new[SCR_CB_SAY];
	if(!callback){
		return qfalse;
	}

	if(mode == 0)
		Scr_AddBool( qfalse );
	else
		Scr_AddBool( qtrue );

	Scr_AddString( textbuf );

	threadId = Scr_ExecEntThread(from, callback, 2);

	Scr_FreeThread(threadId);

	return qtrue;

}

*/
qboolean Scr_ScriptCommand(int clientnum, const char* cmd, const char* args)
{
	int callback;
	int threadId;

	int i, j;

	char textbuf[MAX_STRING_CHARS];
	/* Clean control characters */
	for (i = 0, j = 0; i < sizeof(textbuf) - 1 && args[i]; ++i)
	{
		textbuf[j] = args[i];

		if (textbuf[j] < ' ')
		{
			continue;
		}
		++j;
	}
	textbuf[j] = '\0';

	callback = script_CallBacks_new[SCR_CB_SCRIPTCOMMAND];
	if (!callback)
	{
		Scr_Error(
			"Attempt to call a script added function without a registered callback: "
			"maps/mp/gametypes/_callbacksetup::CodeCallback_ScriptCommand\nMaybe you have not used addscriptcommand() "
			"like it is supposed to use?");
		return qfalse;
	}

	Scr_AddString(textbuf);

	Scr_AddString(cmd);

	if (clientnum < 0 || clientnum > 63)
	{
		threadId = Scr_ExecThread(callback, 2);
	}
	else
	{
		threadId = Scr_ExecEntThread(&g_entities[clientnum], callback, 2);
	}

	Scr_FreeThread(threadId);

	return qtrue;
}
