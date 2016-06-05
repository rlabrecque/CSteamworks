/**********************************************************
 * Only if you have agreed to Valves non-disclosure and/or license
 * agreements only then may you utilize this file under Public Domain.
 *
 * Riley Labrecque - 2013-2016 - Public Domain
 *********************************************************/

#include "CSteamworks.h"

#if defined(VERSION_SAFE_STEAM_API_INTERFACES)
static CSteamAPIContext s_SteamContext;
static CSteamGameServerAPIContext s_SteamGameServerContext;

// These accessors make working with InitSafe() and CSteamAPIContext much easier by providing
// the same interface API that using the regular SteamAPI_Init() provides.
// SteamAPI Accessors:
SB_API ISteamClient *S_CALLTYPE SteamClient() {
	return s_SteamContext.SteamClient();
}

SB_API ISteamUser *S_CALLTYPE SteamUser() {
	return s_SteamContext.SteamUser();
}

SB_API ISteamFriends *S_CALLTYPE SteamFriends() {
	return s_SteamContext.SteamFriends();
}

SB_API ISteamUtils *S_CALLTYPE SteamUtils() {
	return s_SteamContext.SteamUtils();
}

SB_API ISteamMatchmaking *S_CALLTYPE SteamMatchmaking() {
	return s_SteamContext.SteamMatchmaking();
}

SB_API ISteamUserStats *S_CALLTYPE SteamUserStats() {
	return s_SteamContext.SteamUserStats();
}

SB_API ISteamApps *S_CALLTYPE SteamApps() {
	return s_SteamContext.SteamApps();
}

SB_API ISteamNetworking *S_CALLTYPE SteamNetworking() {
	return s_SteamContext.SteamNetworking();
}

SB_API ISteamMatchmakingServers *S_CALLTYPE SteamMatchmakingServers() {
	return s_SteamContext.SteamMatchmakingServers();
}

SB_API ISteamRemoteStorage *S_CALLTYPE SteamRemoteStorage() {
	return s_SteamContext.SteamRemoteStorage();
}

SB_API ISteamScreenshots *S_CALLTYPE SteamScreenshots() {
	return s_SteamContext.SteamScreenshots();
}

SB_API ISteamHTTP *S_CALLTYPE SteamHTTP() {
	return s_SteamContext.SteamHTTP();
}

SB_API ISteamUnifiedMessages *S_CALLTYPE SteamUnifiedMessages() {
	return s_SteamContext.SteamUnifiedMessages();
}

SB_API ISteamController *S_CALLTYPE SteamController() {
	return s_SteamContext.SteamController();
}

SB_API ISteamUGC *S_CALLTYPE SteamUGC() {
	return s_SteamContext.SteamUGC();
}

SB_API ISteamAppList *S_CALLTYPE SteamAppList() {
	return s_SteamContext.SteamAppList();
}

SB_API ISteamMusic *S_CALLTYPE SteamMusic() {
	return s_SteamContext.SteamMusic();
}

SB_API ISteamMusicRemote *S_CALLTYPE SteamMusicRemote() {
	return s_SteamContext.SteamMusicRemote();
}

SB_API ISteamHTMLSurface *S_CALLTYPE SteamHTMLSurface() {
	return s_SteamContext.SteamHTMLSurface();
}

SB_API ISteamInventory *S_CALLTYPE SteamInventory() {
	return s_SteamContext.SteamInventory();
}

SB_API ISteamVideo *S_CALLTYPE SteamVideo() {
	return s_SteamContext.SteamVideo();
}

// GameServer Accessors:
SB_API ISteamClient *S_CALLTYPE SteamGameServerClient() {
	return s_SteamGameServerContext.SteamClient();
}

SB_API ISteamGameServer *S_CALLTYPE SteamGameServer() {
	return s_SteamGameServerContext.SteamGameServer();
}

SB_API ISteamUtils *S_CALLTYPE SteamGameServerUtils() {
	return s_SteamGameServerContext.SteamGameServerUtils();
}

SB_API ISteamNetworking *S_CALLTYPE SteamGameServerNetworking() {
	return s_SteamGameServerContext.SteamGameServerNetworking();
}

SB_API ISteamGameServerStats *S_CALLTYPE SteamGameServerStats() {
	return s_SteamGameServerContext.SteamGameServerStats();
}

SB_API ISteamHTTP *S_CALLTYPE SteamGameServerHTTP() {
	return s_SteamGameServerContext.SteamHTTP();
}

SB_API ISteamInventory *S_CALLTYPE SteamGameServerInventory() {
	return s_SteamGameServerContext.SteamInventory();
}

SB_API ISteamUGC *S_CALLTYPE SteamGameServerUGC() {
	return s_SteamGameServerContext.SteamUGC();
}

SB_API ISteamApps *S_CALLTYPE SteamGameServerApps() {
	return s_SteamGameServerContext.SteamApps();
}
#endif // defined(VERSION_SAFE_STEAM_API_INTERFACES)

/**********************************************************
 * steam_api.h
 *********************************************************/

// Steam API setup & shutdown
#if defined(VERSION_SAFE_STEAM_API_INTERFACES)
SB_API bool S_CALLTYPE InitSafe() {
	bool ret = SteamAPI_InitSafe();

	if (ret) {
		ret = s_SteamContext.Init();
	}

	return ret;
}
#else // defined(VERSION_SAFE_STEAM_API_INTERFACES)
SB_API bool S_CALLTYPE Init() {
	return SteamAPI_Init();
}
#endif // defined(VERSION_SAFE_STEAM_API_INTERFACES)

SB_API void S_CALLTYPE Shutdown() {
	SteamAPI_Shutdown();

#if defined(VERSION_SAFE_STEAM_API_INTERFACES)
	s_SteamContext.Clear();
#endif // defined(VERSION_SAFE_STEAM_API_INTERFACES)
}

SB_API bool S_CALLTYPE RestartAppIfNecessary(uint32 unOwnAppID) {
	return SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

SB_API void S_CALLTYPE ReleaseCurrentThreadMemory() {
	SteamAPI_ReleaseCurrentThreadMemory();
}

// crash dump recording functions
SB_API void S_CALLTYPE WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID) {
	SteamAPI_WriteMiniDump(uStructuredExceptionCode, pvExceptionInfo, uBuildID);
}

SB_API void S_CALLTYPE SetMiniDumpComment(const char *pchMsg) {
	SteamAPI_SetMiniDumpComment(pchMsg);
}

// steam callback and call-result helpers
SB_API void S_CALLTYPE RunCallbacks() {
	SteamAPI_RunCallbacks();
}

SB_API void S_CALLTYPE RegisterCallback(class CCallbackBase *pCallback, int iCallback) {
	SteamAPI_RegisterCallback(pCallback, iCallback);
}

SB_API void S_CALLTYPE UnregisterCallback(class CCallbackBase *pCallback) {
	SteamAPI_UnregisterCallback(pCallback);
}

SB_API void S_CALLTYPE RegisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
	SteamAPI_RegisterCallResult(pCallback, hAPICall);
}

SB_API void S_CALLTYPE UnregisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
	SteamAPI_UnregisterCallResult(pCallback, hAPICall);
}

// steamclient.dll private wrapper functions
SB_API bool S_CALLTYPE IsSteamRunning() {
	return SteamAPI_IsSteamRunning();
}

SB_API void S_CALLTYPE Steam_RunCallbacks_(HSteamPipe hSteamPipe, bool bGameServerCallbacks) {
	Steam_RunCallbacks(hSteamPipe, bGameServerCallbacks);
}

SB_API void S_CALLTYPE Steam_RegisterInterfaceFuncs_(void *hModule) {
	Steam_RegisterInterfaceFuncs(hModule);
}

SB_API HSteamUser S_CALLTYPE Steam_GetHSteamUserCurrent_() {
	return Steam_GetHSteamUserCurrent();
}

SB_API const char *S_CALLTYPE GetSteamInstallPath() {
	return SteamAPI_GetSteamInstallPath();
}

SB_API HSteamPipe S_CALLTYPE GetHSteamPipe_() {
	return SteamAPI_GetHSteamPipe();
}

SB_API void S_CALLTYPE SetTryCatchCallbacks(bool bTryCatchCallbacks) {
	SteamAPI_SetTryCatchCallbacks(bTryCatchCallbacks);
}

/**********************************************************
* steam_api_internal.h
*********************************************************/
SB_API HSteamUser S_CALLTYPE GetHSteamUser_() {
	return SteamAPI_GetHSteamUser();
}

/*
* Unresolved External link error :(
SB_API bool S_CALLTYPE SteamInternal_Init_() {
	return SteamInternal_Init();
}
*/

SB_API void * S_CALLTYPE SteamInternal_CreateInterface_(const char *ver) {
	return SteamInternal_CreateInterface(ver);
}

#if defined(USE_BREAKPAD_HANDLER) || defined(STEAM_API_EXPORTS)
SB_API void S_CALLTYPE UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback) {
	SteamAPI_UseBreakpadCrashHandler(pchVersion, pchDate, pchTime, bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback);
}

SB_API void S_CALLTYPE SetBreakpadAppID(uint32 unAppID) {
	SteamAPI_SetBreakpadAppID(unAppID);
}
#endif // defined(USE_BREAKPAD_HANDLER) || defined(STEAM_API_EXPORTS)

/**********************************************************
 * steam_gameserver.h
 *********************************************************/
SB_API bool S_CALLTYPE GameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	bool ret = SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
	
#ifdef VERSION_SAFE_STEAM_API_INTERFACES
	if (ret) {
		ret = s_SteamGameServerContext.Init();
	}
#endif

	return ret;
}

SB_API void S_CALLTYPE GameServer_Shutdown() {
	SteamGameServer_Shutdown();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
	s_SteamGameServerContext.Clear();
#endif
}

SB_API void S_CALLTYPE GameServer_RunCallbacks() {
	return SteamGameServer_RunCallbacks();
}

SB_API void GameServer_ReleaseCurrentThreadMemory() {
	return SteamGameServer_ReleaseCurrentThreadMemory();
}

SB_API bool S_CALLTYPE GameServer_BSecure() {
	return SteamGameServer_BSecure();
}

SB_API uint64 S_CALLTYPE GameServer_GetSteamID() {
	return SteamGameServer_GetSteamID();
}

// steamclient.dll private wrapper functions
SB_API HSteamPipe S_CALLTYPE GameServer_GetHSteamPipe() {
	return SteamGameServer_GetHSteamPipe();
}

SB_API HSteamUser S_CALLTYPE GameServer_GetHSteamUser() {
	return SteamGameServer_GetHSteamUser();
}

SB_API bool S_CALLTYPE SteamInternal_GameServer_Init_(uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamInternal_GameServer_Init(unIP, usPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}


/**********************************************************
* steamencryptedappticket.h
* You're probably just better off importing from sdkencryptedappticket.dll directly.
*********************************************************/

#if 0
SB_API bool BDecryptTicket(const uint8 *rgubTicketEncrypted, uint32 cubTicketEncrypted, uint8 *rgubTicketDecrypted, uint32 *pcubTicketDecrypted, const uint8 rgubKey[k_nSteamEncryptedAppTicketSymmetricKeyLen], int cubKey) {
	return SteamEncryptedAppTicket_BDecryptTicket(rgubTicketEncrypted, cubTicketEncrypted, rgubTicketDecrypted, pcubTicketDecrypted, rgubKey, cubKey);
}

SB_API bool BIsTicketForApp(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID) {
	return SteamEncryptedAppTicket_BIsTicketForApp(rgubTicketDecrypted, cubTicketDecrypted, nAppID);
}

SB_API RTime32 GetTicketIssueTime(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_GetTicketIssueTime(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API void GetTicketSteamID(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, CSteamID *psteamID) {
	SteamEncryptedAppTicket_GetTicketSteamID(rgubTicketDecrypted, cubTicketDecrypted, psteamID);
}

SB_API AppId_t GetTicketAppID(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_GetTicketAppID(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API bool BUserOwnsAppInTicket(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID) {
	return SteamEncryptedAppTicket_BUserOwnsAppInTicket(rgubTicketDecrypted, cubTicketDecrypted, nAppID);
}

SB_API bool BUserIsVacBanned(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_BUserIsVacBanned(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API const uint8 *GetUserVariableData(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, uint32 *pcubUserData) {
	return SteamEncryptedAppTicket_GetUserVariableData(rgubTicketDecrypted, cubTicketDecrypted, pcubUserData);
}
#endif // 0

#include "unitybuild.cpp"
