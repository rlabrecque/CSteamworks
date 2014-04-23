/**********************************************************
* Only if you have agreed to Valves non-disclosure and/or license
* agreements only then may you utilize this file under Public Domain.
*
* Riley Labrecque - 2013-2014 - Public Domain
*********************************************************/

#ifndef STEAMCALLBACKS_H
#define STEAMCALLBACKS_H

#include "CSteamworks.h"

#ifdef _WIN32
__pragma(warning(push))
__pragma(warning(disable:4355)) // warning C4355: 'this' : used in base member initializer list

typedef void(__stdcall *pfnOnCallback)(int k_iCallback, void *pvParam); # TODO: Marshal the delegate as cdecl
#else
typedef void (__attribute__((cdecl)) *pfnOnCallback)(int k_iCallback, void *pvParam);
#endif


// X Macro so that we can keep both the normal callbacks and game server callbacks in sync.
// We also do this because we have to keep the declaration and instantiation of each callback seperately.
// This ultimately means that this gets called a total of 4 times.
#define LIST_OF_CALLBACKS(X, Y, thisclass) \
	/* isteamapps.h */ \
	X(DlcInstalled_t, thisclass) \
	X(RegisterActivationCodeResponse_t, thisclass) \
	X(AppProofOfPurchaseKeyResponse_t, thisclass) \
	X(NewLaunchQueryParameters_t, thisclass) \
	/* isteamfriends.h */ \
	X(PersonaStateChange_t, thisclass) \
	X(GameOverlayActivated_t, thisclass) \
	X(GameServerChangeRequested_t, thisclass) \
	X(GameLobbyJoinRequested_t, thisclass) \
	X(AvatarImageLoaded_t, thisclass) \
	X(ClanOfficerListResponse_t, thisclass) \
	X(FriendRichPresenceUpdate_t, thisclass) \
	X(GameRichPresenceJoinRequested_t, thisclass) \
	X(GameConnectedClanChatMsg_t, thisclass) \
	X(GameConnectedChatJoin_t, thisclass) \
	X(GameConnectedChatLeave_t, thisclass) \
	X(DownloadClanActivityCountsResult_t, thisclass) \
	X(JoinClanChatRoomCompletionResult_t, thisclass) \
	X(GameConnectedFriendChatMsg_t, thisclass) \
	X(FriendsGetFollowerCount_t, thisclass) \
	X(FriendsIsFollowing_t, thisclass) \
	X(FriendsEnumerateFollowingList_t, thisclass) \
	X(SetPersonaNameResponse_t, thisclass) \
	/* isteamgamecoordinator.h */ \
	X(GCMessageAvailable_t, thisclass) \
	X(GCMessageFailed_t, thisclass) \
	/* isteamgameserver.h */ \
	X(GSClientApprove_t, thisclass) \
	X(GSClientDeny_t, thisclass) \
	X(GSClientKick_t, thisclass) \
	X(GSClientAchievementStatus_t, thisclass) \
	X(GSPolicyResponse_t, thisclass) \
	X(GSGameplayStats_t, thisclass) \
	X(GSClientGroupStatus_t, thisclass) \
	X(GSReputation_t, thisclass) \
	X(AssociateWithClanResult_t, thisclass) \
	X(ComputeNewPlayerCompatibilityResult_t, thisclass) \
	/* isteamgameserverstats.h */ \
	X(GSStatsReceived_t, thisclass) \
	X(GSStatsStored_t, thisclass) \
	X(GSStatsUnloaded_t, thisclass) \
	/* isteamhttp.h */ \
	X(HTTPRequestCompleted_t, thisclass) \
	X(HTTPRequestHeadersReceived_t, thisclass) \
	X(HTTPRequestDataReceived_t, thisclass) \
	/* isteammatchmaking.h */ \
	X(FavoritesListChanged_t, thisclass) \
	X(LobbyInvite_t, thisclass) \
	X(LobbyEnter_t, thisclass) \
	X(LobbyDataUpdate_t, thisclass) \
	X(LobbyChatUpdate_t, thisclass) \
	X(LobbyChatMsg_t, thisclass) \
	X(LobbyGameCreated_t, thisclass) \
	X(LobbyMatchList_t, thisclass) \
	X(LobbyKicked_t, thisclass) \
	X(LobbyCreated_t, thisclass) \
	/* isteamnetworking.h */ \
	X(P2PSessionRequest_t, thisclass) \
	X(P2PSessionConnectFail_t, thisclass) \
	X(SocketStatusCallback_t, thisclass) \
	/* isteamremotestorage.h */ \
	X(RemoteStorageAppSyncedClient_t, thisclass) \
	X(RemoteStorageAppSyncedServer_t, thisclass) \
	X(RemoteStorageAppSyncProgress_t, thisclass) \
	X(RemoteStorageAppSyncStatusCheck_t, thisclass) \
	X(RemoteStorageConflictResolution_t, thisclass) \
	X(RemoteStorageFileShareResult_t, thisclass) \
	X(RemoteStoragePublishFileResult_t, thisclass) \
	X(RemoteStorageDeletePublishedFileResult_t, thisclass) \
	X(RemoteStorageEnumerateUserPublishedFilesResult_t, thisclass) \
	X(RemoteStorageSubscribePublishedFileResult_t, thisclass) \
	X(RemoteStorageEnumerateUserSubscribedFilesResult_t, thisclass) \
	X(RemoteStorageUnsubscribePublishedFileResult_t, thisclass) \
	X(RemoteStorageUpdatePublishedFileResult_t, thisclass) \
	X(RemoteStorageDownloadUGCResult_t, thisclass) \
	X(RemoteStorageGetPublishedFileDetailsResult_t, thisclass) \
	X(RemoteStorageEnumerateWorkshopFilesResult_t, thisclass) \
	X(RemoteStorageGetPublishedItemVoteDetailsResult_t, thisclass) \
	X(RemoteStoragePublishedFileSubscribed_t, thisclass) \
	X(RemoteStoragePublishedFileUnsubscribed_t, thisclass) \
	X(RemoteStoragePublishedFileDeleted_t, thisclass) \
	X(RemoteStorageUpdateUserPublishedItemVoteResult_t, thisclass) \
	X(RemoteStorageUserVoteDetails_t, thisclass) \
	X(RemoteStorageEnumerateUserSharedWorkshopFilesResult_t, thisclass) \
	X(RemoteStorageSetUserPublishedFileActionResult_t, thisclass) \
	X(RemoteStorageEnumeratePublishedFilesByUserActionResult_t, thisclass) \
	X(RemoteStoragePublishFileProgress_t, thisclass) \
	X(RemoteStoragePublishedFileUpdated_t, thisclass) \
	/* isteamscreenshots.h */ \
	X(ScreenshotReady_t, thisclass) \
	X(ScreenshotRequested_t, thisclass) \
	/* isteamugc.h */ \
	X(SteamUGCQueryCompleted_t, thisclass) \
	X(SteamUGCRequestUGCDetailsResult_t, thisclass) \
	/* isteamunifiedmessages.h */ \
	X(SteamUnifiedMessagesSendMethodResult_t, thisclass) \
	/* isteamuser.h */ \
	X(SteamServersConnected_t, thisclass) \
	X(SteamServerConnectFailure_t, thisclass) \
	X(SteamServersDisconnected_t, thisclass) \
	X(ClientGameServerDeny_t, thisclass) \
	X(IPCFailure_t, thisclass) \
	X(ValidateAuthTicketResponse_t, thisclass) \
	X(MicroTxnAuthorizationResponse_t, thisclass) \
	X(EncryptedAppTicketResponse_t, thisclass) \
	X(GetAuthSessionTicketResponse_t, thisclass) \
	X(GameWebCallback_t, thisclass) \
	/* isteamuserstats.h */ \
	X(UserStatsReceived_t, thisclass) \
	X(UserStatsStored_t, thisclass) \
	X(UserAchievementStored_t, thisclass) \
	X(LeaderboardFindResult_t, thisclass) \
	X(LeaderboardScoresDownloaded_t, thisclass) \
	X(LeaderboardScoreUploaded_t, thisclass) \
	X(NumberOfCurrentPlayers_t, thisclass) \
	X(UserStatsUnloaded_t, thisclass) \
	X(UserAchievementIconFetched_t, thisclass) \
	X(GlobalAchievementPercentagesReady_t, thisclass) \
	X(LeaderboardUGCSet_t, thisclass) \
	X(GlobalStatsReceived_t, thisclass) \
	/* isteamutils.h */ \
	X(IPCountry_t, thisclass) \
	X(LowBatteryPower_t, thisclass) \
	X(SteamAPICallCompleted_t, thisclass) \
	X(SteamShutdown_t, thisclass) \
	X(CheckFileSignature_t, thisclass) \
	Y(GamepadTextInputDismissed_t, thisclass)

#define REGISTER_CSTEAMWORKS_CALLBACK( thisclass, param ) m_##param(this, &thisclass::fn_##param)

#define CSTEAMWORKS_CALLBACK(thisclass, param, bserver, handler) \
	CCallback<thisclass, param, bserver> m_##param; \
	void fn_##param(param *pParam) { if (handler) handler(param::k_iCallback, pParam); }

// Want to see something scary?
// Don't do this at home kids.
// If you're an employer potentially looking to hire me avert your eyes now!

// Each X requires a following comma, Y is the last item in the list and must not have a comma.
#define REGISTER_CALLBACK_Y(name, thisclass) REGISTER_CSTEAMWORKS_CALLBACK(thisclass, name)
#define REGISTER_CALLBACK_X(name, thisclass) REGISTER_CALLBACK_Y(name, thisclass),

#define DEFINE_CLIENT_CALLBACK(name, thisclass) CSTEAMWORKS_CALLBACK(thisclass, name, false, g_apiCallbacksHandler);

#define DEFINE_SERVER_CALLBACK(name, thisclass) CSTEAMWORKS_CALLBACK(thisclass, name, true, g_serverCallbacksHandler);

// Never let the callback classes get out of sync with eachother.
#define GENERATE_CALLBACK_CLASS(thisclass, definecallbackmacro) \
	class thisclass { \
	public: \
		thisclass() : LIST_OF_CALLBACKS(REGISTER_CALLBACK_X, REGISTER_CALLBACK_Y, thisclass) { } \
		LIST_OF_CALLBACKS(definecallbackmacro, definecallbackmacro, thisclass) \
	}

//=============================================================================
pfnOnCallback g_apiCallbacksHandler = nullptr;
GENERATE_CALLBACK_CLASS(SteamCallbacks, DEFINE_CLIENT_CALLBACK);
//=============================================================================
pfnOnCallback g_serverCallbacksHandler = nullptr;
GENERATE_CALLBACK_CLASS(SteamGameServerCallbacks, DEFINE_SERVER_CALLBACK);
//=============================================================================

#undef GENERATE_CALLBACK_CLASS

#undef DEFINE_CLIENT_CALLBACK
#undef DEFINE_SERVER_CALLBACK

#undef REGISTER_CALLBACK_Y
#undef REGISTER_CALLBACK_X

#undef CSTEAMWORKS_CALLBACK
#undef REGISTER_CSTEAMWORKS_CALLBACK
#undef LIST_OF_CALLBACKS

#ifdef _WIN32
__pragma(warning(pop)) // warning C4355: 'this' : used in base member initializer list
#endif

#endif // STEAMCALLBACKS_H
