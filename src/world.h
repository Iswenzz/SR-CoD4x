struct SentientHandle
{
	uint16_t number;
	uint16_t infoIndex;
};

enum NodeType
{
	NODE_BADNODE = 0x0,
	NODE_PATHNODE = 0x1,
	NODE_COVER_STAND = 0x2,
	NODE_COVER_CROUCH = 0x3,
	NODE_COVER_CROUCH_WINDOW = 0x4,
	NODE_COVER_PRONE = 0x5,
	NODE_COVER_RIGHT = 0x6,
	NODE_COVER_LEFT = 0x7,
	NODE_COVER_WIDE_RIGHT = 0x8,
	NODE_COVER_WIDE_LEFT = 0x9,
	NODE_CONCEALMENT_STAND = 0xA,
	NODE_CONCEALMENT_CROUCH = 0xB,
	NODE_CONCEALMENT_PRONE = 0xC,
	NODE_REACQUIRE = 0xD,
	NODE_BALCONY = 0xE,
	NODE_SCRIPTED = 0xF,
	NODE_NEGOTIATION_BEGIN = 0x10,
	NODE_NEGOTIATION_END = 0x11,
	NODE_TURRET = 0x12,
	NODE_GUARD = 0x13,
	NODE_NUMTYPES = 0x14,
	NODE_DONTLINK = 0x14,
};

struct NodeTypeToName
{
	NodeType type;
	const char *name;
};

struct PathLinkInfo
{
	unsigned short from;
	unsigned short to;
	unsigned short prev;
	unsigned short next;
};

struct pathlocal_t_tag
{
	float origin[3];
	float maxDist;
	float maxDistSq;
	float maxHeightSq;
	int typeFlags;
	struct pathsort_t *nodes;
	int maxNodes;
	int nodeCount;
};

struct __align(128) pathlocal_t
{
	PathLinkInfo pathLinkInfoArray[2048];
	int pathLinkInfoArrayInited;
	unsigned int actualNodeCount;
	unsigned int extraNodes;
	unsigned int originErrors;
	pathlocal_t_tag circle;
};

struct pathnodeRange_t
{
	float minSqDist;
	float fAngleMin;
	float fAngleMax;
};

struct pathsort_t
{
	struct pathnode_t *node;
	float metric;
	float distMetric;
};

struct pathlink_s
{
	float fDist;
	unsigned short nodeNum;
	unsigned char disconnectCount;
	unsigned char negotiationLink;
	unsigned char ubBadPlaceCount[4];
};

struct pathnode_constant_t
{
	NodeType type;
	unsigned short spawnflags;
	unsigned short targetname;
	unsigned short script_linkName;
	unsigned short script_noteworthy;
	unsigned short target;
	unsigned short animscript;
	int animscriptfunc;
	float vOrigin[3];
	float fAngle;
	float forward[2];
	float fRadius;
	float minUseDistSq;
	short wOverlapNode[2];
	short wChainId;
	short wChainDepth;
	short wChainParent;
	unsigned short totalLinkCount;
	pathlink_s *Links;
};

struct pathnode_dynamic_t
{
	SentientHandle pOwner;
	int iFreeTime;
	int iValidTime[3];
	int inPlayerLOSTime;
	short wLinkCount;
	short wOverlapCount;
	short turretEntNumber;
	short userCount;
};

struct pathnode_transient_t
{
	int iSearchFrame;
	struct pathnode_t *pNextOpen;
	struct pathnode_t *pPrevOpen;
	struct pathnode_t *pParent;
	float fCost;
	float fHeuristic;
	float costFactor;
};

struct pathnode_t
{
	pathnode_constant_t constant;
	pathnode_dynamic_t dynamic;
	pathnode_transient_t transient;
};

struct pathbasenode_t
{
	float vOrigin[3];
	unsigned int type;
};

struct pathnode_tree_nodes_t
{
	int nodeCount;
	unsigned short *nodes;
};

struct pathnode_tree_t;

union pathnode_tree_info_t
{
	pathnode_tree_t *child[2];
	pathnode_tree_nodes_t s;
};

struct pathnode_tree_t
{
	int axis;
	float dist;
	pathnode_tree_info_t u;
};
struct PathData
{
	PathData()
	{
		memset(this, 0, sizeof(PathData));
	}
	unsigned int nodeCount;
	pathnode_t *nodes;
	pathbasenode_t *basenodes;
	unsigned int chainNodeCount;
	unsigned short *chainNodeForNode;
	unsigned short *nodeForChainNode;
	int visBytes;
	unsigned char *pathVis;
	int nodeTreeCount;
	pathnode_tree_t *nodeTree;
};

struct GameWorldMp
{
	const char *name;
};

struct GameWorldSp
{
	const char *name;
	PathData path;
};

struct ComWorld
{
	const char *name;
	int isInUse;
	unsigned int primaryLightCount;
	struct ComPrimaryLight *primaryLights;
};

extern struct ComWorld comWorld;
extern struct GameWorldMp gameWorldMp;
extern struct GameWorldSp gameWorldSp;
