#include "q3files.h"
// #include "surfaceflags.h"

typedef struct
{
	vec3_t xyz;
	vec3_t normal;
	byte color[4];
	float st[2];
	float lightmap[2];
	vec3_t tangent;
	vec3_t binormal;
} iw3_drawVert_t;

extern int iw3_nummodels;
extern q3_dmodel_t *iw3_dmodels; //[Q3_MAX_MAP_MODELS];

extern int iw3_numShaders;
extern q3_dshader_t *iw3_dshaders; //[Q3_MAX_MAP_SHADERS];

extern int iw3_entdatasize;
extern char *iw3_dentdata; //[Q3_MAX_MAP_ENTSTRING];

extern int iw3_numleafs;
extern q3_dleaf_t *iw3_dleafs; //[Q3_MAX_MAP_LEAFS];

extern int iw3_numplanes;
extern q3_dplane_t *iw3_dplanes; //[Q3_MAX_MAP_PLANES];

extern int iw3_numnodes;
extern q3_dnode_t *iw3_dnodes; //[Q3_MAX_MAP_NODES];

extern int iw3_numleafsurfaces;
extern int *iw3_dleafsurfaces; //[Q3_MAX_MAP_LEAFFACES];

extern int iw3_numleafbrushes;
extern int *iw3_dleafbrushes; //[Q3_MAX_MAP_LEAFBRUSHES];

extern int iw3_numbrushes;
extern q3_dbrush_t *iw3_dbrushes; //[Q3_MAX_MAP_BRUSHES];

extern int iw3_numbrushsides;
extern q3_dbrushside_t *iw3_dbrushsides; //[IW3_MAX_MAP_BRUSHSIDES];

extern int iw3_numLightBytes;
extern byte *iw3_lightBytes; //[Q3_MAX_MAP_LIGHTING];

extern int iw3_numGridPoints;
extern byte *iw3_gridData; //[Q3_MAX_MAP_LIGHTGRID];

extern int iw3_numVisBytes;
extern byte *iw3_visBytes; //[Q3_MAX_MAP_VISIBILITY];

extern int iw3_numDrawVerts;
extern iw3_drawVert_t *iw3_drawVerts; //[Q3_MAX_MAP_DRAW_VERTS];

extern int iw3_numDrawIndexes;
extern uint16_t *iw3_drawIndexes; //[Q3_MAX_MAP_DRAW_INDEXES];

extern int iw3_numDrawSurfaces;
extern q3_dsurface_t *iw3_drawSurfaces; //[Q3_MAX_MAP_DRAW_SURFS];

extern int iw3_numFogs;
extern q3_dfog_t *iw3_dfogs; //[Q3_MAX_MAP_FOGS];

extern char iw3_dbrushsidetextured[IW3_MAX_MAP_BRUSHSIDES];

void IW3_LoadFastfile(struct quakefile_s *qf);
void IW3_FreeMaxBSP(void);
void IW3_ParseEntities(void);
