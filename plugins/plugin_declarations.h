
#define PLUGIN_HANDLER_VERSION_MAJOR 4
#define PLUGIN_HANDLER_VERSION_MINOR 000
// PHandler v. 2.2

enum Plugin_Err
{					  // To be used as the code argument for Plugin_Error()
	P_ERROR_WARNING,  // Save the error string to serverlog - for minor errors
	P_ERROR_DISABLE,  // Save the error string to serverlog and disable the plugin - for serious errors
	P_ERROR_TERMINATE // Save the error string to serverlog and close the server - for critical errors
};
typedef enum
{
	P_HASH_SHA1,
	P_HASH_SHA256,
	P_HASH_TIGER
} pluginHash_t;

typedef enum
{
	P_CIPHER_AES,
	P_CIPHER_SERPENT
} pluginCipher_t;

typedef struct
{
	int major;
	int minor;
} version_t;

typedef struct
{								// To be used in OnInfoRequest
	version_t handlerVersion;	// Requested plugin handler version - mandatory field
	version_t pluginVersion;	// Version of your plugin - optional
	char fullName[64];			// Full plugin name, short name is the filename without extension - optional
	char shortDescription[128]; // Describe in a few words what this plugin does - optional
	char longDescription[1024]; // Full description - optional
} pluginInfo_t;
