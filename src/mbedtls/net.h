
#if !defined(MBEDTLS_CONFIG_FILE)
	#include "config.h"
#else
	#include MBEDTLS_CONFIG_FILE
#endif

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
	#include "net_sockets.h"
	#if defined(MBEDTLS_DEPRECATED_WARNING)
		#warning "Deprecated header file: Superseded by mbedtls/net_sockets.h"
	#endif /* MBEDTLS_DEPRECATED_WARNING */
#endif	   /* !MBEDTLS_DEPRECATED_REMOVED */
