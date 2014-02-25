/**********************************************************
 * This file contains content that is Copyright of Valve Corporation.
 * As such, this file is exempt from the LICENSE.txt agreement.
 * If you have agreed to Valves non-disclosure and/or license agreements
 * only then may you utilize this file under Public Domain.
 *
 * Riley Labrecque - 2013 - Public Domain
 *********************************************************/

#include "CSteamworks.h"

static CSteamAPIContext s_SteamContext;
static CSteamGameServerAPIContext s_SteamGameServerContext;

/**********************************************************
 * This makes working with InitSafe / CSteamAPIContext much easier.
 * An alternative would be to extern s_SteamContext and call each wrapped function through s_SteamContext directly.
 * That would require two versions of each wrapped function, one being for VERSION_SAFE_[...]
 *********************************************************/
#ifdef VERSION_SAFE_STEAM_API_INTERFACES
// SteamAPI Accessors:
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
#ifdef _PS3
SB_API ISteamPS3OverlayRender *S_CALLTYPE SteamPS3OverlayRender() {
	return s_SteamContext.SteamPS3OverlayRender();
}
#endif // _PS3

// GameServer Accessors:
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
	return s_SteamGameServerContext.SteamHTTP(); // This should have been named SteamGameServerHTTP, but it's inconsistent for some reason.
}
#endif // VERSION_SAFE_STEAM_API_INTERFACES

/**********************************************************
 * steam_api.h
 *********************************************************/

SB_API void S_CALLTYPE Shutdown() {
	SteamAPI_Shutdown();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
	s_SteamContext.Clear();
#endif
}

SB_API bool S_CALLTYPE IsSteamRunning() {
	return SteamAPI_IsSteamRunning();
}

SB_API bool S_CALLTYPE RestartAppIfNecessary(uint32 unOwnAppID) {
	return SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

SB_API void S_CALLTYPE WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID) {
	SteamAPI_WriteMiniDump(uStructuredExceptionCode, pvExceptionInfo, uBuildID);
}

SB_API void S_CALLTYPE SetMiniDumpComment(const char *pchMsg) {
	SteamAPI_SetMiniDumpComment(pchMsg);
}

SB_API ISteamClient *S_CALLTYPE SteamClient_() {
	return SteamClient();
}

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool S_CALLTYPE InitSafe() {
	bool ret = SteamAPI_InitSafe();
	
	if (ret) {
		ret = s_SteamContext.Init();
	}

	return ret;
}

#else

#if defined(_PS3)
SB_API bool S_CALLTYPE Init(SteamPS3Params_t *pParams) {
	return SteamAPI_Init(pParams);
}
#else
SB_API bool S_CALLTYPE Init() {
	return SteamAPI_Init();
}
#endif

//SB_API ISteamUser *S_CALLTYPE SteamUser();
//SB_API ISteamFriends *S_CALLTYPE SteamFriends();
//SB_API ISteamUtils *S_CALLTYPE SteamUtils();
//SB_API ISteamMatchmaking *S_CALLTYPE SteamMatchmaking();
//SB_API ISteamUserStats *S_CALLTYPE SteamUserStats();
//SB_API ISteamApps *S_CALLTYPE SteamApps();
//SB_API ISteamNetworking *S_CALLTYPE SteamNetworking();
//SB_API ISteamMatchmakingServers *S_CALLTYPE SteamMatchmakingServers();
//SB_API ISteamRemoteStorage *S_CALLTYPE SteamRemoteStorage();
//SB_API ISteamScreenshots *S_CALLTYPE SteamScreenshots();
//SB_API ISteamHTTP *S_CALLTYPE SteamHTTP();
//SB_API ISteamUnifiedMessages *S_CALLTYPE SteamUnifiedMessages();
#ifdef _PS3
//SB_API ISteamPS3OverlayRender *S_CALLTYPE SteamPS3OverlayRender();
#endif
#endif // VERSION_SAFE_STEAM_API_INTERFACES

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

//Legacy accessors, deprecated
//SB_API HSteamPipe S_CALLTYPE GetHSteamPipe();
//SB_API HSteamUser S_CALLTYPE GetHSteamUser();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API HSteamUser S_CALLTYPE GetHSteamUser_() {
	return SteamAPI_GetHSteamUser();
}
#endif // VERSION_SAFE_STEAM_API_INTERFACES

#if defined(USE_BREAKPAD_HANDLER) || defined(STEAM_API_EXPORTS)
SB_API void S_CALLTYPE UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback) {
	SteamAPI_UseBreakpadCrashHandler(pchVersion, pchDate, pchTime, bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback);
}

SB_API void S_CALLTYPE SetBreakpadAppID(uint32 unAppID) {
	SteamAPI_SetBreakpadAppID(unAppID);
}
#endif

/**********************************************************
 * steam_gameserver.h
 *********************************************************/
#ifndef _PS3

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool S_CALLTYPE GameServer_InitSafe(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	bool ret = SteamGameServer_InitSafe(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);

	if (ret) {
		ret = s_SteamGameServerContext.Init();
	}

	return ret;
}
#else
SB_API bool S_CALLTYPE GameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}
#endif

#else

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool S_CALLTYPE GameServer_InitSafe(const SteamPS3Params_t *ps3Params, uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	bool ret = SteamGameServer_InitSafe(ps3Params, unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);

	if (ret) {
		ret = s_SteamGameServerContext.Init();
	}

	return ret;
}
#else
SB_API bool S_CALLTYPE GameServer_Init(const SteamPS3Params_t *ps3Params, uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_Init(ps3Params, unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}
#endif

#endif

#ifndef VERSION_SAFE_STEAM_API_INTERFACES
//SB_API ISteamGameServer *S_CALLTYPE SteamGameServer();
//SB_API ISteamUtils *S_CALLTYPE SteamGameServerUtils();
//SB_API ISteamNetworking *S_CALLTYPE SteamGameServerNetworking();
//SB_API ISteamGameServerStats *S_CALLTYPE SteamGameServerStats();
//SB_API ISteamHTTP *S_CALLTYPE SteamGameServerHTTP();
#endif

SB_API void S_CALLTYPE GameServer_Shutdown() {
	SteamGameServer_Shutdown();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
	s_SteamGameServerContext.Clear();
#endif
}

SB_API void S_CALLTYPE GameServer_RunCallbacks() {
	return SteamGameServer_RunCallbacks();
}

SB_API bool S_CALLTYPE GameServer_BSecure() {
	return SteamGameServer_BSecure();
}

SB_API uint64 S_CALLTYPE GameServer_GetSteamID() {
	return SteamGameServer_GetSteamID();
}

SB_API HSteamPipe S_CALLTYPE GameServer_GetHSteamPipe() {
	return SteamGameServer_GetHSteamPipe();
}

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API HSteamUser S_CALLTYPE GameServer_GetHSteamUser() {
	return SteamGameServer_GetHSteamUser();
}
#endif

SB_API ISteamClient *SteamClientGameServer() {
	return g_pSteamClientGameServer;
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

/**********************************************************
 * steamclient.dll wrapper functions
 * These expose the required functionality to write a custom Steam_RunCallbacks() function
 *********************************************************/

typedef bool (__cdecl * BGetCallback_t)(HSteamPipe, CallbackMsg_t *);
typedef void (__cdecl * FreeLastCallback_t)(HSteamPipe);
typedef bool (__cdecl * GetAPICallResult_t)(HSteamPipe, SteamAPICall_t, void *, int, int, bool *);

#if defined( _WIN32 )
#define WINVER 0x0501 //WinXP
#define _WIN32_WINNT 0x0501 //WinXP
#define WIN32_LEAN_AND_MEAN
#define STRICT
#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
#define NOUSER
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#include <windows.h> // God Damn it Windows.
#include <stdio.h> // fprintf

#ifdef _WIN64
static const char *s_SteamClientDLLName = "steamclient64.dll";
#else
static const char *s_SteamClientDLLName = "steamclient.dll";
#endif

SB_API bool __cdecl Steam_BGetCallback2(HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg) {
	static BGetCallback_t _Steam_BGetCallback = NULL;
	if(!_Steam_BGetCallback) {
		HMODULE hSteamClient = GetModuleHandleA(s_SteamClientDLLName);
		if(hSteamClient) {
			_Steam_BGetCallback = reinterpret_cast<BGetCallback_t>(GetProcAddress(hSteamClient, "Steam_BGetCallback"));

			if(!_Steam_BGetCallback) {
				fprintf(stderr, "[CSteamworks] GetProcAddress failed to find Steam_BGetCallback\n");
				return false;
			}
		}
		else {
			fprintf(stderr, "[CSteamworks] GetModuleHandleA failed opening steamclient.dll\n");
			return false;
		}
	}
	
	return _Steam_BGetCallback(hSteamPipe, pCallbackMsg);
}

SB_API void __cdecl Steam_FreeLastCallback2(HSteamPipe hSteamPipe) {
	static FreeLastCallback_t _Steam_FreeLastCallback = NULL;
	if(!_Steam_FreeLastCallback) {
		HMODULE hSteamClient = GetModuleHandleA(s_SteamClientDLLName);
		if(hSteamClient) {
			_Steam_FreeLastCallback = reinterpret_cast<FreeLastCallback_t>(GetProcAddress(hSteamClient, "Steam_FreeLastCallback"));
			
			if(!_Steam_FreeLastCallback) {
				fprintf(stderr, "[CSteamworks] GetProcAddress failed to find Steam_FreeLastCallback\n");
				return;
			}
		}
		else {
			fprintf(stderr, "[CSteamworks] GetModuleHandleA failed opening steamclient.dll\n");
			return;
		}
	}
	
	return _Steam_FreeLastCallback(hSteamPipe);
}

SB_API bool __cdecl Steam_GetAPICallResult2(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed) {
	static GetAPICallResult_t _Steam_GetAPICallResult = NULL;
	if(!_Steam_GetAPICallResult) {
		HMODULE hSteamClient = GetModuleHandleA(s_SteamClientDLLName);
		if(hSteamClient) {
			_Steam_GetAPICallResult = reinterpret_cast<GetAPICallResult_t>(GetProcAddress(hSteamClient, "Steam_GetAPICallResult"));
			
			if(!_Steam_GetAPICallResult) {
				fprintf(stderr, "[CSteamworks] GetProcAddress failed to find Steam_GetAPICallResult\n");
				return false;
			}
		}
		else {
			fprintf(stderr, "[CSteamworks] GetModuleHandleA failed opening steamclient.dll\n");
			return false;
		}
	}

	return _Steam_GetAPICallResult(hSteamPipe, hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}

#elif defined( __APPLE__ )

#include <dlfcn.h> // dlopen, dlsym, dlclose
#include <stdio.h> // fprintf

SB_API bool Steam_BGetCallback2(HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg) {
	static BGetCallback_t _Steam_BGetCallback = NULL;
	if(!_Steam_BGetCallback) {
		_Steam_BGetCallback = reinterpret_cast<BGetCallback_t>(dlsym(RTLD_DEFAULT, "Steam_BGetCallback"));
			
		if(!_Steam_BGetCallback) {
			fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_BGetCallback\n");
			return false;
		}
	}
	
	return _Steam_BGetCallback(hSteamPipe, pCallbackMsg);
}

SB_API void __cdecl Steam_FreeLastCallback2(HSteamPipe hSteamPipe) {
	static FreeLastCallback_t _Steam_FreeLastCallback = NULL;
	if(!_Steam_FreeLastCallback) {
		_Steam_FreeLastCallback = reinterpret_cast<FreeLastCallback_t>(dlsym(RTLD_DEFAULT, "Steam_FreeLastCallback"));
			
		if(!_Steam_FreeLastCallback) {
			fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_FreeLastCallback\n");
			return;
		}
	}
	
	return _Steam_FreeLastCallback(hSteamPipe);
}

SB_API bool __cdecl Steam_GetAPICallResult2(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed) {
	static GetAPICallResult_t _Steam_GetAPICallResult = NULL;
	if(!_Steam_GetAPICallResult)
	{
		_Steam_GetAPICallResult = reinterpret_cast<GetAPICallResult_t>(dlsym(RTLD_DEFAULT, "Steam_GetAPICallResult"));
		
		if(!_Steam_GetAPICallResult) {
			fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_GetAPICallResult\n");
			return false;
		}
	}
	
	return _Steam_GetAPICallResult(hSteamPipe, hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}

#elif defined( __linux__ )

#include <dlfcn.h> // dlopen, dlsym, dlclose
#include <stdio.h> // fprintf
#include <stdlib.h> // getenv
#include <limits.h> // PATH_MAX

#ifdef __x86_64__
static const char *s_sdkDir = "sdk64";
#else
static const char *s_sdkDir = "sdk32";
#endif

static char s_resolved_path[PATH_MAX];
static const char* GetSteamClientPath() {
	static bool _once = false;
	if(!_once) {
		int cx = snprintf(s_resolved_path, PATH_MAX, "%s/.steam/%s/steamclient.so", getenv("HOME"), s_sdkDir);
		if(cx < 0 || cx > PATH_MAX) {
			fprintf(stderr, "[CSteamworks] snprintf failed\n");
		}
		_once = true;
	}
	return s_resolved_path;
}

SB_API bool Steam_BGetCallback2(HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg) {
	static BGetCallback_t _Steam_BGetCallback = NULL;
	if(!_Steam_BGetCallback) {
		void* hSteamClient = dlopen(GetSteamClientPath(), RTLD_LAZY);
		if(hSteamClient) {
			_Steam_BGetCallback = reinterpret_cast<BGetCallback_t>(dlsym(hSteamClient, "Steam_BGetCallback"));
			dlclose(hSteamClient);

			if(!_Steam_BGetCallback) {
				fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_BGetCallback\n");
				return false;
			}
		}
		else {
			fprintf(stderr, "[CSteamworks] dlopen failed opening steamclient.so\n");
			return false;
		}
	}
	
	return _Steam_BGetCallback(hSteamPipe, pCallbackMsg);
}

SB_API void __cdecl Steam_FreeLastCallback2(HSteamPipe hSteamPipe) {
	static FreeLastCallback_t _Steam_FreeLastCallback = NULL;
	if(!_Steam_FreeLastCallback) {
			void* hSteamClient = dlopen(GetSteamClientPath(), RTLD_LAZY);
			if(hSteamClient) {
				_Steam_FreeLastCallback = reinterpret_cast<FreeLastCallback_t>(dlsym(hSteamClient, "Steam_FreeLastCallback"));
				dlclose(hSteamClient);

				if(!_Steam_FreeLastCallback) {
					fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_FreeLastCallback\n");
					return;
				}
			}
			else {
				fprintf(stderr, "[CSteamworks] dlopen failed opening steamclient.so\n");
				return;
			}
	}

	return _Steam_FreeLastCallback(hSteamPipe);
}

SB_API bool __cdecl Steam_GetAPICallResult2(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed) {
	static GetAPICallResult_t _Steam_GetAPICallResult = NULL;
	if(!_Steam_GetAPICallResult)
	{
		void* hSteamClient = dlopen(GetSteamClientPath(), RTLD_LAZY);
		if(hSteamClient) {
			_Steam_GetAPICallResult = reinterpret_cast<GetAPICallResult_t>(dlsym(hSteamClient, "Steam_GetAPICallResult"));
			dlclose(hSteamClient);

			if(!_Steam_GetAPICallResult) {
				fprintf(stderr, "[CSteamworks] dlsym failed to find Steam_GetAPICallResult\n");
				return false;
			}
		}
		else {
			fprintf(stderr, "[CSteamworks] dlopen failed opening steamclient.so\n");
			return false;
		}
	}
	
	return _Steam_GetAPICallResult(hSteamPipe, hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
}
#endif
