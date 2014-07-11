/**********************************************************
* Only if you have agreed to Valves non-disclosure and/or license
* agreements only then may you utilize this file under Public Domain.
*
* Riley Labrecque - 2013-2014 - Public Domain
*********************************************************/

#ifndef CSTEAMWORKS_H
#define CSTEAMWORKS_H

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

#define SB_API extern "C"  __declspec( dllexport )
#elif defined( GNUC )
#define SB_API extern "C" __attribute__ ((visibility ("default")))
#else
#define SB_API extern "C"
#endif

// A few functions return CSteamID which can not be done when using extern "C"
// We could slam it directly to uint64, but that doesn't give other wrappers the info they require for autogen.
typedef uint64 SteamID_t;

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API ISteamUser *S_CALLTYPE SteamUser();
SB_API ISteamFriends *S_CALLTYPE SteamFriends();
SB_API ISteamUtils *S_CALLTYPE SteamUtils();
SB_API ISteamMatchmaking *S_CALLTYPE SteamMatchmaking();
SB_API ISteamUserStats *S_CALLTYPE SteamUserStats();
SB_API ISteamApps *S_CALLTYPE SteamApps();
SB_API ISteamNetworking *S_CALLTYPE SteamNetworking();
SB_API ISteamMatchmakingServers *S_CALLTYPE SteamMatchmakingServers();
SB_API ISteamRemoteStorage *S_CALLTYPE SteamRemoteStorage();
SB_API ISteamScreenshots *S_CALLTYPE SteamScreenshots();
SB_API ISteamHTTP *S_CALLTYPE SteamHTTP();
SB_API ISteamUnifiedMessages *S_CALLTYPE SteamUnifiedMessages();
SB_API ISteamController *S_CALLTYPE SteamController();
SB_API ISteamUGC *S_CALLTYPE SteamUGC();
SB_API ISteamAppList *S_CALLTYPE SteamAppList();
SB_API ISteamMusic *S_CALLTYPE SteamMusic();
SB_API ISteamMusicRemote *S_CALLTYPE SteamMusicRemote();
#ifdef _PS3
SB_API ISteamPS3OverlayRender *S_CALLTYPE SteamPS3OverlayRender();
#endif // _PS3

SB_API ISteamGameServer *S_CALLTYPE SteamGameServer();
SB_API ISteamUtils *S_CALLTYPE SteamGameServerUtils();
SB_API ISteamNetworking *S_CALLTYPE SteamGameServerNetworking();
SB_API ISteamGameServerStats *S_CALLTYPE SteamGameServerStats();
SB_API ISteamHTTP *S_CALLTYPE SteamGameServerHTTP();
#endif // VERSION_SAFE_STEAM_API_INTERFACES

#endif // CSTEAMWORKS_H
