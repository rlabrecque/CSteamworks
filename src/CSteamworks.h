/**********************************************************
* Only if you have agreed to Valves non-disclosure and/or license
* agreements only then may you utilize this file under Public Domain.
*
* Riley Labrecque - 2013-2017 - Public Domain
*********************************************************/

#pragma once

#if defined( _WIN32 )
__pragma(warning(push))
__pragma(warning(disable:4127)) // 'conditional expression is constant'
__pragma(warning(disable:4996)) // 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead.
#endif
#include "steam_gameserver.h" // Includes steam_api internally
#include "steamencryptedappticket.h"
#include "isteamgamecoordinator.h"
#if defined( _WIN32 )
__pragma(warning(pop))
#endif

#if defined( _WIN32 ) && CSTEAMWORKS_DLLEXPORT
#define SB_API extern "C"  __declspec( dllexport )
#elif defined( GNUC ) && CSTEAMWORKS_DLLEXPORT
#define SB_API extern "C" __attribute__ ((visibility ("default")))
#else
#define SB_API extern "C"
#endif

// A few functions return CSteamID which can not be done when using extern "C"
// We could slam it directly to uint64, but that doesn't give other wrappers the info they require for autogen.
typedef uint64 SteamID_t;
