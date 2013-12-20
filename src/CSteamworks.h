#ifndef CSTEAMWORKS_H
#define CSTEAMWORKS_H

#include "steam_gameserver.h" // Includes steam_api internally

#if defined( _WIN32 )
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
ISteamUser *S_CALLTYPE SteamUser();
ISteamFriends *S_CALLTYPE SteamFriends();
ISteamUtils *S_CALLTYPE SteamUtils();
ISteamMatchmaking *S_CALLTYPE SteamMatchmaking();
ISteamUserStats *S_CALLTYPE SteamUserStats();
ISteamApps *S_CALLTYPE SteamApps();
ISteamNetworking *S_CALLTYPE SteamNetworking();
ISteamMatchmakingServers *S_CALLTYPE SteamMatchmakingServers();
ISteamRemoteStorage *S_CALLTYPE SteamRemoteStorage();
ISteamScreenshots *S_CALLTYPE SteamScreenshots();
ISteamHTTP *S_CALLTYPE SteamHTTP();
ISteamUnifiedMessages *S_CALLTYPE SteamUnifiedMessages();
ISteamController *S_CALLTYPE SteamController();
ISteamUGC *S_CALLTYPE SteamUGC();
#ifdef _PS3
ISteamPS3OverlayRender *S_CALLTYPE SteamPS3OverlayRender();
#endif // _PS3

ISteamGameServer *S_CALLTYPE SteamGameServer();
ISteamUtils *S_CALLTYPE SteamGameServerUtils();
ISteamNetworking *S_CALLTYPE SteamGameServerNetworking();
ISteamGameServerStats *S_CALLTYPE SteamGameServerStats();
ISteamHTTP *S_CALLTYPE SteamGameServerHTTP();

// I'm sorry, I hate doing this too :(
// We replicate CSteamAPIContext without SteamController support solely because of Unity on Linux.
// More details here: http://steamcommunity.com/groups/steamworks/discussions/13/666827315255279716/#c666827315260524314
class CSteamAPIContext2
{
public:
	CSteamAPIContext2();
	void Clear();

	bool Init();

	ISteamUser*			SteamUser()							{ return m_pSteamUser; }
	ISteamFriends*		SteamFriends()						{ return m_pSteamFriends; }
	ISteamUtils*		SteamUtils()						{ return m_pSteamUtils; }
	ISteamMatchmaking*	SteamMatchmaking()					{ return m_pSteamMatchmaking; }
	ISteamUserStats*	SteamUserStats()					{ return m_pSteamUserStats; }
	ISteamApps*			SteamApps()							{ return m_pSteamApps; }
	ISteamMatchmakingServers*	SteamMatchmakingServers()	{ return m_pSteamMatchmakingServers; }
	ISteamNetworking*	SteamNetworking()					{ return m_pSteamNetworking; }
	ISteamRemoteStorage* SteamRemoteStorage()				{ return m_pSteamRemoteStorage; }
	ISteamScreenshots*	SteamScreenshots()					{ return m_pSteamScreenshots; }
	ISteamHTTP*			SteamHTTP()							{ return m_pSteamHTTP; }
	ISteamUnifiedMessages*	SteamUnifiedMessages()			{ return m_pSteamUnifiedMessages; }
	//ISteamController*	SteamController()					{ return m_pController; }
	ISteamUGC*			SteamUGC()							{ return m_pSteamUGC; }
#ifdef _PS3
	ISteamPS3OverlayRender* SteamPS3OverlayRender()		{ return m_pSteamPS3OverlayRender; }
#endif

private:
	ISteamUser		*m_pSteamUser;
	ISteamFriends	*m_pSteamFriends;
	ISteamUtils		*m_pSteamUtils;
	ISteamMatchmaking	*m_pSteamMatchmaking;
	ISteamUserStats		*m_pSteamUserStats;
	ISteamApps			*m_pSteamApps;
	ISteamMatchmakingServers	*m_pSteamMatchmakingServers;
	ISteamNetworking	*m_pSteamNetworking;
	ISteamRemoteStorage *m_pSteamRemoteStorage;
	ISteamScreenshots	*m_pSteamScreenshots;
	ISteamHTTP			*m_pSteamHTTP;
	ISteamUnifiedMessages*m_pSteamUnifiedMessages;
	//ISteamController	*m_pController;
	ISteamUGC			*m_pSteamUGC;
#ifdef _PS3
	ISteamPS3OverlayRender *m_pSteamPS3OverlayRender;
#endif
};

inline CSteamAPIContext2::CSteamAPIContext2()
{
	Clear();
}

inline void CSteamAPIContext2::Clear()
{
	m_pSteamUser = NULL;
	m_pSteamFriends = NULL;
	m_pSteamUtils = NULL;
	m_pSteamMatchmaking = NULL;
	m_pSteamUserStats = NULL;
	m_pSteamApps = NULL;
	m_pSteamMatchmakingServers = NULL;
	m_pSteamNetworking = NULL;
	m_pSteamRemoteStorage = NULL;
	m_pSteamHTTP = NULL;
	m_pSteamScreenshots = NULL;
	m_pSteamUnifiedMessages = NULL;
	//m_pController = NULL;
	m_pSteamUGC = NULL;
#ifdef _PS3
	m_pSteamPS3OverlayRender = NULL;
#endif
}

// This function must be inlined so the module using steam_api.dll gets the version names they want.
inline bool CSteamAPIContext2::Init()
{
	if (!SteamClient())
		return false;

	HSteamUser hSteamUser = SteamAPI_GetHSteamUser();
	HSteamPipe hSteamPipe = SteamAPI_GetHSteamPipe();

	m_pSteamUser = SteamClient()->GetISteamUser(hSteamUser, hSteamPipe, STEAMUSER_INTERFACE_VERSION);
	if (!m_pSteamUser)
		return false;

	m_pSteamFriends = SteamClient()->GetISteamFriends(hSteamUser, hSteamPipe, STEAMFRIENDS_INTERFACE_VERSION);
	if (!m_pSteamFriends)
		return false;

	m_pSteamUtils = SteamClient()->GetISteamUtils(hSteamPipe, STEAMUTILS_INTERFACE_VERSION);
	if (!m_pSteamUtils)
		return false;

	m_pSteamMatchmaking = SteamClient()->GetISteamMatchmaking(hSteamUser, hSteamPipe, STEAMMATCHMAKING_INTERFACE_VERSION);
	if (!m_pSteamMatchmaking)
		return false;

	m_pSteamMatchmakingServers = SteamClient()->GetISteamMatchmakingServers(hSteamUser, hSteamPipe, STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION);
	if (!m_pSteamMatchmakingServers)
		return false;

	m_pSteamUserStats = SteamClient()->GetISteamUserStats(hSteamUser, hSteamPipe, STEAMUSERSTATS_INTERFACE_VERSION);
	if (!m_pSteamUserStats)
		return false;

	m_pSteamApps = SteamClient()->GetISteamApps(hSteamUser, hSteamPipe, STEAMAPPS_INTERFACE_VERSION);
	if (!m_pSteamApps)
		return false;

	m_pSteamNetworking = SteamClient()->GetISteamNetworking(hSteamUser, hSteamPipe, STEAMNETWORKING_INTERFACE_VERSION);
	if (!m_pSteamNetworking)
		return false;

	m_pSteamRemoteStorage = SteamClient()->GetISteamRemoteStorage(hSteamUser, hSteamPipe, STEAMREMOTESTORAGE_INTERFACE_VERSION);
	if (!m_pSteamRemoteStorage)
		return false;

	m_pSteamScreenshots = SteamClient()->GetISteamScreenshots(hSteamUser, hSteamPipe, STEAMSCREENSHOTS_INTERFACE_VERSION);
	if (!m_pSteamScreenshots)
		return false;

	m_pSteamHTTP = SteamClient()->GetISteamHTTP(hSteamUser, hSteamPipe, STEAMHTTP_INTERFACE_VERSION);
	if (!m_pSteamHTTP)
		return false;

	m_pSteamUnifiedMessages = SteamClient()->GetISteamUnifiedMessages(hSteamUser, hSteamPipe, STEAMUNIFIEDMESSAGES_INTERFACE_VERSION);
	if (!m_pSteamUnifiedMessages)
		return false;

	//m_pController = SteamClient()->GetISteamController(hSteamUser, hSteamPipe, STEAMCONTROLLER_INTERFACE_VERSION);
	//if (!m_pController)
	//	return false;

	m_pSteamUGC = SteamClient()->GetISteamUGC(hSteamUser, hSteamPipe, STEAMUGC_INTERFACE_VERSION);
	if (!m_pSteamUGC)
		return false;

#ifdef _PS3
	m_pSteamPS3OverlayRender = SteamClient()->GetISteamPS3OverlayRender();
#endif

	return true;
}
#endif // VERSION_SAFE_STEAM_API_INTERFACES

#endif // CSTEAMWORKS_H
