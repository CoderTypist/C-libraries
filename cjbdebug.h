// Author: Christian Bargraser

#ifndef _CJB_DEBUG_H_
#define _CJB_DEBUG_H_

#include <stdbool.h>

extern bool bVerbose;
extern bool bDebug;

// macros
#define VERBOSE if ( true == bVerbose )
#define DEBUG if ( true == bDebug )
#define NOT_VERBOSE if ( false == bVerbose )
#define NOT_DEBUG if( false == bDebug )
#define FLAG(x) fprintf(stderr, "Flag: %d\n", x);
#define VFLAG(x) if ( true == bVerbose ) { fprintf(stderr, "Flag: %d\n", x); }
#define DFLAG(x) if ( true == bDebug ) { fprintf(stderr, "Flag: %d\n", x); }

#endif // _CJB_DEBUG_H_
