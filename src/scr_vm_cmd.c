#include "q_shared.h"
#include "qcommon_io.h"
#include "qcommon_mem.h"
#include "scr_vm.h"

#include <string.h>

scr_function_t *scr_functions = NULL;
scr_method_t *scr_methods = NULL;

qboolean Scr_AddFunction(const char *cmd_name, xfunction_t function, qboolean developer)
{
	scr_function_t *cmd;

	// fail if the command already exists
	for (cmd = scr_functions; cmd; cmd = cmd->next)
	{
		if (!strcmp(cmd_name, cmd->name))
		{
			// allow completion-only commands to be silently doubled
			if (function != NULL)
			{
				Com_PrintWarning(CON_CHANNEL_SCRIPT, "Scr_AddFunction: %s already defined\n", cmd_name);
			}
			return qfalse;
		}
	}

	// use a small malloc to avoid zone fragmentation
	cmd = S_Malloc(sizeof(scr_function_t) + strlen(cmd_name) + 1);
	strcpy((char *)(cmd + 1), cmd_name);
	cmd->name = (char *)(cmd + 1);
	cmd->function = function;
	cmd->developer = developer;
	cmd->next = scr_functions;
	scr_functions = cmd;
	return qtrue;
}

qboolean Scr_RemoveFunction(const char *cmd_name)
{
	scr_function_t *cmd, **back;

	back = &scr_functions;
	while (1)
	{
		cmd = *back;
		if (!cmd)
		{
			// command wasn't active
			return qfalse;
		}
		if (!strcmp(cmd_name, cmd->name))
		{
			*back = cmd->next;
			Z_Free(cmd);
			return qtrue;
		}
		back = &cmd->next;
	}
	return qfalse;
}

void Scr_ClearFunctions()
{
	scr_function_t *cmd, **back;

	int i = 0;

	while (1)
	{
		back = &scr_functions;
		cmd = *back;
		if (!cmd)
		{
			// This was the last script function
			return;
		}
		*back = cmd->next;
		Z_Free(cmd);
		i++;
	}
}

__cdecl void *Scr_GetFunction(const char **v_functionName, qboolean *v_developer)
{
	scr_function_t *cmd;

	for (cmd = scr_functions; cmd != NULL; cmd = cmd->next)
	{
		if (!Q_stricmp(*v_functionName, cmd->name))
		{
			*v_developer = cmd->developer;
			*v_functionName = cmd->name;
			return cmd->function;
		}
	}
	return NULL;
}

qboolean Scr_AddMethod(const char *cmd_name, xmethod_t method, qboolean developer)
{
	scr_method_t *cmd;

	// fail if the command already exists
	for (cmd = scr_methods; cmd; cmd = cmd->next)
	{
		if (!strcmp(cmd_name, cmd->name))
		{
			// allow completion-only commands to be silently doubled
			if (method != NULL)
			{
				Com_PrintWarning(CON_CHANNEL_SCRIPT, "Scr_AddMethod: %s already defined\n", cmd_name);
			}
			return qfalse;
		}
	}

	// use a small malloc to avoid zone fragmentation
	cmd = S_Malloc(sizeof(scr_function_t) + strlen(cmd_name) + 1);
	strcpy((char *)(cmd + 1), cmd_name);
	cmd->name = (char *)(cmd + 1);
	cmd->function = (xfunction_t)method;
	cmd->developer = developer;
	cmd->next = scr_methods;
	scr_methods = cmd;
	return qtrue;
}

qboolean Scr_RemoveMethod(const char *cmd_name)
{
	scr_method_t *cmd, **back;

	back = &scr_methods;
	while (1)
	{
		cmd = *back;
		if (!cmd)
		{
			// command wasn't active
			return qfalse;
		}
		if (!strcmp(cmd_name, cmd->name))
		{
			*back = cmd->next;
			Z_Free(cmd);
			return qtrue;
		}
		back = &cmd->next;
	}
	return qfalse;
}

void Scr_ClearMethods()
{
	scr_method_t *cmd, **back;

	int i = 0;

	while (1)
	{
		back = &scr_methods;
		cmd = *back;
		if (!cmd)
		{
			// This was the last script method
			return;
		}
		*back = cmd->next;
		Z_Free(cmd);
		i++;
	}
}

__cdecl void *Scr_GetMethod(const char **v_functionName, qboolean *v_developer)
{
	scr_method_t *cmd;

	for (cmd = scr_methods; cmd != NULL; cmd = cmd->next)
	{
		if (!Q_stricmp(*v_functionName, cmd->name))
		{
			*v_developer = cmd->developer;
			*v_functionName = cmd->name;
			return cmd->function;
		}
	}
	return NULL;
}

qboolean Scr_IsSyscallDefined(const char *name)
{
	scr_method_t *pMethod;
	scr_function_t *pFunction;

	for (pMethod = scr_methods; pMethod != NULL; pMethod = pMethod->next)
		if (!Q_stricmp(name, pMethod->name))
			return qtrue;

	for (pFunction = scr_functions; pFunction != NULL; pFunction = pFunction->next)
		if (!Q_stricmp(name, pFunction->name))
			return qtrue;

	return qfalse;
}
