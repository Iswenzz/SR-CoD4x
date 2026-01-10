#include "q_shared.h"
#include "player.h"

qboolean OnSameTeam(gentity_t *ent1, gentity_t *ent2)
{
	if (!ent1->client || !ent2->client)
	{
		return qfalse;
	}
	if (ent1->client->sess.cs.team == TEAM_FREE)
	{
		return qfalse;
	}

	if (ent1->client->sess.cs.team == ent2->client->sess.cs.team)
	{
		return qtrue;
	}

	return qfalse;
}

/*
OnSameTeam
*//*
qboolean OnSameTeamCLNum( int num1, int num2 ) {
	gentity_t *ent1 = g_entities[num1];
	gentity_t *ent2 = g_entities[num2];

	if ( !ent1->client || !ent2->client ) {
		return qfalse;
	}

	if ( g_gametype.integer < GT_TEAM ) {
		return qfalse;
	}

	if ( ent1->client->sess.sessionTeam == ent2->client->sess.sessionTeam ) {
		return qtrue;
	}

	return qfalse;
}
*/
