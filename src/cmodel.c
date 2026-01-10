#include "q_shared.h"
#include "cm_local.h"

void CM_ModelBounds(clipHandle_t model, vec3_t mins, vec3_t maxs)
{
	cmodel_t *cmod;

	cmod = CM_ClipHandleToModel(model);
	VectorCopy(cmod->mins, mins);
	VectorCopy(cmod->maxs, maxs);
}
