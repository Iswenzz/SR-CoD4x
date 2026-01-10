
//
// Name:			cfg.h
// Function:
// Programmer:		Mr Elusive (MrElusive@demigod.demon.nl)
// Last update:		1997-12-04
// Tab Size:		3

#define BBOXFL_GROUNDED 1	 // bounding box only valid when on ground
#define BBOXFL_NOTGROUNDED 2 // bounding box only valid when NOT on ground

typedef struct cfg_s
{
	int numbboxes;					   // number of bounding boxes
	aas_bbox_t bboxes[AAS_MAX_BBOXES]; // all the bounding boxes
	int allpresencetypes;			   // or of all presence types
	// aas settings
	vec3_t phys_gravitydirection;
	float phys_friction;
	float phys_stopspeed;
	float phys_gravity;
	float phys_waterfriction;
	float phys_watergravity;
	float phys_maxvelocity;
	float phys_maxwalkvelocity;
	float phys_maxcrouchvelocity;
	float phys_maxswimvelocity;
	float phys_walkaccelerate;
	float phys_airaccelerate;
	float phys_swimaccelerate;
	float phys_maxstep;
	float phys_maxsteepness;
	float phys_maxwaterjump;
	float phys_maxbarrier;
	float phys_jumpvel;
	float phys_falldelta5;
	float phys_falldelta10;
	float rs_waterjump;
	float rs_teleport;
	float rs_barrierjump;
	float rs_startcrouch;
	float rs_startgrapple;
	float rs_startwalkoffledge;
	float rs_startjump;
	float rs_rocketjump;
	float rs_bfgjump;
	float rs_jumppad;
	float rs_aircontrolledjumppad;
	float rs_funcbob;
	float rs_startelevator;
	float rs_falldamage5;
	float rs_falldamage10;
	float rs_maxjumpfallheight;
} cfg_t;

extern cfg_t cfg;

void DefaultCfg(void);
int LoadCfgFile(char *filename);
