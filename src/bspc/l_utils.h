
//
// Name:         l_utils.h
// Function:     several utils
// Programmer:   Mr Elusive (MrElusive@demigod.demon.nl)
// Last update:  1997-12-31
// Tab Size:     3

#ifndef MAX_PATH
	#define MAX_PATH 64
#endif

#ifndef PATH_SEPERATORSTR
	#if defined(WIN32) | defined(_WIN32) | defined(__NT__) | defined(__WINDOWS__) | defined(__WINDOWS_386__)
		#define PATHSEPERATOR_STR "\\"
	#else
		#define PATHSEPERATOR_STR "/"
	#endif
#endif
#ifndef PATH_SEPERATORCHAR
	#if defined(WIN32) | defined(_WIN32) | defined(__NT__) | defined(__WINDOWS__) | defined(__WINDOWS_386__)
		#define PATHSEPERATOR_CHAR '\\'
	#else
		#define PATHSEPERATOR_CHAR '/'
	#endif
#endif

// random in the range [0, 1]
#define random() ((rand() & 0x7fff) / ((float)0x7fff))
// random in the range [-1, 1]
#define crandom() (2.0 * (random() - 0.5))
// min and max
#define Maximum(x, y) (x > y ? x : y)
#define Minimum(x, y) (x < y ? x : y)
// absolute value
#define FloatAbs(x) (*(float *)&((*(int *)&(x)) & 0x7FFFFFFF))
#define IntAbs(x) (~(x))
// coordinates
#define _X 0
#define _Y 1
#define _Z 2

typedef struct foundfile_s
{
	int offset;
	int length;
	char filename[MAX_PATH]; // screw LCC, array must be at end of struct
} foundfile_t;

void Vector2Angles(vec3_t value1, vec3_t angles);
// set the correct path seperators
void ConvertPath(char *path);
// append a path seperator to the given path not exceeding the length
void AppendPathSeperator(char *path, int length);
// find a file in a pak file
qboolean FindFileInPak(char *pakfile, char *filename, foundfile_t *file);
// find a quake file
#ifdef BOTLIB
qboolean FindQuakeFile(char *filename, foundfile_t *file);
#else  // BOTLIB
qboolean FindQuakeFile(char *basedir, char *gamedir, char *filename, foundfile_t *file);
#endif // BOTLIB
