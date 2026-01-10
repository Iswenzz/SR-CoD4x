#ifndef __CMD_COMPLETION_H__
#define __CMD_COMPLETION_H__

#include "cvar.h"
#include "cmd.h"
/*

Edit fields and command line history/completion

*/
// typedef void (*completionFunc_t)( char *args, int argNum );

#define MAX_EDIT_LINE 256
typedef struct
{
	int cursor;
	int scroll;
	int len;
	char buffer[MAX_EDIT_LINE];
} field_t;

void Cvar_CommandCompletionPrint(cvar_t const *cvar, void *none);
void Cvar_CommandCompletionFind(cvar_t const *cvar, void *none);
void Cvar_CompleteCvarName(char *args, int argNum);

void Field_Clear(field_t *edit);
void Field_CompleteCommand(char *cmd, qboolean doCommands, qboolean doCvars);
void Field_AutoComplete(field_t *field);

#endif
