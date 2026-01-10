/*****************************************************************************
 * name:		be_aas_routealt.h
 *
 * desc:		AAS
 *
 *
 *****************************************************************************/

#ifdef AASINTERN
void AAS_InitAlternativeRouting(void);
void AAS_ShutdownAlternativeRouting(void);
#endif // AASINTERN

int AAS_AlternativeRouteGoals(vec3_t start, vec3_t goal, int travelflags, aas_altroutegoal_t *altroutegoals,
	int maxaltroutegoals, int color);
