#ifndef MAX_MAP_ENTITIES
	#define MAX_MAP_ENTITIES 2048
#endif

typedef struct epair_s
{
	struct epair_s *next;
	char *key;
	char *value;
} epair_t;

typedef struct
{
	vec3_t origin;
	int firstbrush;
	int numbrushes;
	epair_t *epairs;
	// only valid for func_areaportals
	int areaportalnum;
	int portalareas[2];
	int modelnum;		// for bsp 2 map conversion
	qboolean wasdetail; // for SIN
} entity_t;

extern int num_entities;
extern entity_t entities[MAX_MAP_ENTITIES];

void StripTrailing(char *e);
void SetKeyValue(entity_t *ent, char *key, char *value);
char *ValueForKey(entity_t *ent, char *key); // will return "" if not present
vec_t FloatForKey(entity_t *ent, char *key);
void GetVectorForKey(entity_t *ent, char *key, vec3_t vec);
qboolean ParseEntity(script_t *script);
epair_t *ParseEpair(script_t *script);
void PrintEntity(entity_t *ent);
