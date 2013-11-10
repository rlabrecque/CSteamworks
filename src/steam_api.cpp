/**********************************************************
 * This File contains content that is Copyright of Valve Corporation.
 * This File is exempt from the LICENSE.txt agreement.
 * If you have agreed to Valves non-disclosure and/or license agreement
 * only then may you utilize this file under Public Domain.
 *
 * Riley Labrecque - 2013 - Public Domain
 *********************************************************/

#include "steam_api.h"
#include "steam_gameserver.h"
#include "steamencryptedappticket.h"

#if defined( _WIN32 )
#define SB_API extern "C"  __declspec( dllexport )
#elif defined( GNUC )
#define SB_API extern "C" __attribute__ ((visibility ("default")))
#else
#define SB_API extern "C"
#endif

/**********************************************************
 * steam_api.h
 *********************************************************/

SB_API void Shutdown() {
	SteamAPI_Shutdown();
}

SB_API bool IsSteamRunning() {
	return SteamAPI_IsSteamRunning();
}

SB_API bool RestartAppIfNecessary(uint32 unOwnAppID) {
	return SteamAPI_RestartAppIfNecessary(unOwnAppID);
}

SB_API void WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID) {
	SteamAPI_WriteMiniDump(uStructuredExceptionCode, pvExceptionInfo, uBuildID);
}

SB_API void SetMiniDumpComment(const char *pchMsg) {
	SteamAPI_SetMiniDumpComment(pchMsg);
}

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool InitSafe() {
	return SteamAPI_InitSafe();
}
#else

#if defined(_PS3)
SB_API bool Init(SteamPS3Params_t *pParams) {
	return SteamAPI_Init(pParams);
}
#else
SB_API bool Init() {
	return SteamAPI_Init();
}
#endif

//SB_API ISteamUser *SteamUser();
//SB_API ISteamFriends *SteamFriends();
//SB_API ISteamUtils *SteamUtils();
//SB_API ISteamMatchmaking *SteamMatchmaking();
//SB_API ISteamUserStats *SteamUserStats();
//SB_API ISteamApps *SteamApps();
//SB_API ISteamNetworking *SteamNetworking();
//SB_API ISteamMatchmakingServers *SteamMatchmakingServers();
//SB_API ISteamRemoteStorage *SteamRemoteStorage();
//SB_API ISteamScreenshots *SteamScreenshots();
//SB_API ISteamHTTP *SteamHTTP();
//SB_API ISteamUnifiedMessages *SteamUnifiedMessages();
#ifdef _PS3
//SB_API ISteamPS3OverlayRender * SteamPS3OverlayRender();
#endif
#endif // VERSION_SAFE_STEAM_API_INTERFACES

SB_API void RunCallbacks() {
	SteamAPI_RunCallbacks();
}

SB_API void RegisterCallback(class CCallbackBase *pCallback, int iCallback) {
	SteamAPI_RegisterCallback(pCallback, iCallback);
}

SB_API void UnregisterCallback(class CCallbackBase *pCallback) {
	SteamAPI_UnregisterCallback(pCallback);
}

SB_API void RegisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
	SteamAPI_RegisterCallResult(pCallback, hAPICall);
}

SB_API void UnregisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
	SteamAPI_UnregisterCallResult(pCallback, hAPICall);
}

SB_API void Steam_RunCallbacks_(HSteamPipe hSteamPipe, bool bGameServerCallbacks) {
	Steam_RunCallbacks(hSteamPipe, bGameServerCallbacks);
}

SB_API void Steam_RegisterInterfaceFuncs_(void *hModule) {
	Steam_RegisterInterfaceFuncs(hModule);
}

SB_API HSteamUser Steam_GetHSteamUserCurrent_() {
	return Steam_GetHSteamUserCurrent();
}

SB_API const char *GetSteamInstallPath() {
	return SteamAPI_GetSteamInstallPath();
}

SB_API HSteamPipe GetHSteamPipe_() {
	return SteamAPI_GetHSteamPipe();
}

SB_API void SetTryCatchCallbacks(bool bTryCatchCallbacks) {
	SteamAPI_SetTryCatchCallbacks(bTryCatchCallbacks);
}

//SB_API HSteamPipe GetHSteamPipe();
//SB_API HSteamUser GetHSteamUser();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API HSteamUser GetHSteamUser() {
	return SteamAPI_GetHSteamUser();
}
#endif // VERSION_SAFE_STEAM_API_INTERFACES

#if defined(USE_BREAKPAD_HANDLER) || defined(STEAM_API_EXPORTS)
SB_API void SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback) {
	SteamAPI_UseBreakpadCrashHandler(pchVersion, pchDate, pchTime, bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback)
}

SB_API void SetBreakpadAppID(uint32 unAppID) {
	SteamAPI_SetBreakpadAppID(uint32 unAppID);
}
#endif

/**********************************************************
 * steam_gameserver.h
 *********************************************************/

#ifndef _PS3

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool GameServer_InitSafe(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_InitSafe(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString)
}
#else
SB_API bool GameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_Init(unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}
#endif

#else

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
SB_API bool GameServer_InitSafe(const SteamPS3Params_t *ps3Params, uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_InitSafe(ps3Params, unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}
#else
SB_API bool GameServer_Init(const SteamPS3Params_t *ps3Params, uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString) {
	return SteamGameServer_Init(ps3Params, unIP, usSteamPort, usGamePort, usQueryPort, eServerMode, pchVersionString);
}
#endif

#endif

/**********************************************************
 * steamencryptedappticket.h
 *********************************************************/

#if 0
SB_API bool EncryptedAppTicket_BDecryptTicket(const uint8 *rgubTicketEncrypted, uint32 cubTicketEncrypted, uint8 *rgubTicketDecrypted, uint32 *pcubTicketDecrypted, const uint8 rgubKey[k_nSteamEncryptedAppTicketSymmetricKeyLen], int cubKey) {
	return SteamEncryptedAppTicket_BDecryptTicket(rgubTicketEncrypted, cubTicketEncrypted, rgubTicketDecrypted, pcubTicketDecrypted, rgubKey, cubKey);
}

SB_API bool EncryptedAppTicket_BIsTicketForApp(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID) {
	return SteamEncryptedAppTicket_BIsTicketForApp(rgubTicketDecrypted, cubTicketDecrypted, nAppID);
}

SB_API RTime32 EncryptedAppTicket_GetTicketIssueTime(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_GetTicketIssueTime(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API void EncryptedAppTicket_GetTicketSteamID(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, CSteamID *psteamID) {
	SteamEncryptedAppTicket_GetTicketSteamID(rgubTicketDecrypted, cubTicketDecrypted, psteamID);
}

SB_API AppId_t EncryptedAppTicket_GetTicketAppID(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_GetTicketAppID(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API bool EncryptedAppTicket_BUserOwnsAppInTicket(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID) {
	return SteamEncryptedAppTicket_BUserOwnsAppInTicket(rgubTicketDecrypted, cubTicketDecrypted, nAppID);
}

SB_API bool EncryptedAppTicket_BUserIsVacBanned(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted) {
	return SteamEncryptedAppTicket_BUserIsVacBanned(rgubTicketDecrypted, cubTicketDecrypted);
}

SB_API const uint8 *EncryptedAppTicket_GetUserVariableData(uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, uint32 *pcubUserData) {
	return SteamEncryptedAppTicket_GetUserVariableData(rgubTicketDecrypted, cubTicketDecrypted, pcubUserData);
}
#endif // 0

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

SB_API bool __cdecl Steam_BGetCallback2(HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg) {
	static BGetCallback_t _Steam_BGetCallback = NULL;
	if(!_Steam_BGetCallback) {
		HMODULE hSteamClient = GetModuleHandleA("steamclient.dll");
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
		HMODULE hSteamClient = GetModuleHandleA("steamclient.dll");
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
		HMODULE hSteamClient = GetModuleHandleA("steamclient.dll");
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

static char s_resolved_path[PATH_MAX];
static const char* GetSteamClientPath() {
	static bool _once = false;
	if(!_once) {
		int cx = snprintf(s_resolved_path, PATH_MAX, "%s/.steam/sdk32/steamclient.so", getenv("HOME"));
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
