import os
import sys
from shutil import copyfile
from SteamworksParser import steamworksparser

g_SkippedFiles = (
    # We don't currently support the following interfaces because they don't provide a factory of their own.
    # You are expected to call GetISteamGeneric to get them.
    "isteamappticket.h",
    "isteamgamecoordinator.h",
    # PS3 is not supported.
    "isteamps3overlayrenderer.h",
)

g_MissingAttribsDict = {
    # These args are missing a clang attribute like ARRAY_COUNT
    'ISteamAppList_GetInstalledApps': {
        'pvecAppID': steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'unMaxAppIDs'),
    },
    'ISteamAppList_GetAppInstallDir': {
        'pchDirectory': steamworksparser.ArgAttribute('OUT_STRING', ''),
    },
    "ISteamApps_GetInstalledDepots": {
        "pvecDepots": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cMaxDepots'),
    },
    "ISteamApps_GetCurrentBetaName": {
        "pchName": steamworksparser.ArgAttribute('OUT_STRING', ''),
    },
    "ISteamApps_BGetDLCDataByIndex": {
        "pchName": steamworksparser.ArgAttribute('OUT_STRING', ''),
    },
    'ISteamApps_GetAppInstallDir': {
        'pchFolder': steamworksparser.ArgAttribute('OUT_STRING', ''),
    },
    "ISteamController_GetConnectedControllers": {
        "handlesOut": steamworksparser.ArgAttribute('OUT_ARRAY_CONSTANT', 'STEAM_CONTROLLER_MAX_COUNT'),
    },
    "ISteamController_GetDigitalActionOrigins": {
        "originsOut": steamworksparser.ArgAttribute('OUT_ARRAY_CONSTANT', 'STEAM_CONTROLLER_MAX_ORIGINS'),
    },
    "ISteamController_GetAnalogActionOrigins": {
        "originsOut": steamworksparser.ArgAttribute('OUT_ARRAY_CONSTANT', 'STEAM_CONTROLLER_MAX_ORIGINS'),
    },
    "ISteamGameServer_SendUserConnectAndAuthenticate": {
        "pvAuthBlob": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cubAuthBlobSize'),
    },
    "ISteamGameServer_GetAuthSessionTicket": {
        "pTicket": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbMaxTicket'),
    },
    "ISteamGameServer_BeginAuthSession": {
        "pAuthTicket": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cbAuthTicket'),
    },
    "ISteamGameServer_HandleIncomingPacket": {
        "pData": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbData'),
    },
    "ISteamGameServer_GetNextOutgoingPacket": {
        "pOut": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbMaxOut'),
    },
    "ISteamHTTP_GetHTTPResponseHeaderValue": {
        "pHeaderValueBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'unBufferSize'),
    },
    "ISteamHTTP_GetHTTPResponseBodyData": {
        "pBodyDataBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'unBufferSize'),
    },
    "ISteamHTTP_GetHTTPStreamingResponseBodyData": {
        "pBodyDataBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'unBufferSize'),
    },
    "ISteamHTTP_SetHTTPRequestRawPostBody": {
        "pubBody": steamworksparser.ArgAttribute('ARRAY_COUNT', 'unBodyLen'),
    },
    "ISteamInventory_DeserializeResult": {
        "pBuffer": steamworksparser.ArgAttribute('BUFFER_COUNT', 'unBufferSize'),
    },
    "ISteamMatchmaking_SendLobbyChatMsg": {
        "pvMsgBody": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubMsgBody'),
    },
    "ISteamMatchmaking_GetLobbyChatEntry": {
        "pvData": steamworksparser.ArgAttribute('OUT_BUFFER_COUNT', 'cubData'),
    },
    "ISteamMusicRemote_SetPNGIcon_64x64": {
        "pvBuffer": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cbBufferLength'),
    },
    "ISteamMusicRemote_UpdateCurrentEntryCoverArt": {
        "pvBuffer": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cbBufferLength'),
    },
    "ISteamNetworking_SendP2PPacket": {
        "pubData": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubData'),
    },
    "ISteamNetworking_ReadP2PPacket": {
        "pubDest": steamworksparser.ArgAttribute('OUT_BUFFER_COUNT', 'pcubMsgSize'),
    },
    "ISteamNetworking_SendDataOnSocket": {
        "pubData": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubData'),
    },
    "ISteamNetworking_RetrieveDataFromSocket": {
        "pubDest": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubDest'),
    },
    "ISteamNetworking_RetrieveData": {
        "pubDest": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubDest'),
    },
    "ISteamRemoteStorage_FileWrite": {
        "pvData": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubData'),
    },
    "ISteamRemoteStorage_FileRead": {
        "pvData": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cubDataToRead'),
    },
    "ISteamRemoteStorage_FileWriteAsync": {
        "pvData": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubData'),
    },
    "ISteamRemoteStorage_FileReadAsyncComplete": {
        "pvBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cubToRead'),
    },
    "ISteamRemoteStorage_FileWriteStreamWriteChunk": {
        "pvData": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubData'),
    },
    "ISteamRemoteStorage_UGCRead": {
        "pvData": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cubDataToRead'),
    },
    "ISteamScreenshots_WriteScreenshot": {
        "pubRGB": steamworksparser.ArgAttribute('BUFFER_COUNT', 'cubRGB'),
    },
    "ISteamUGC_CreateQueryUGCDetailsRequest": {
        "pvecPublishedFileID": steamworksparser.ArgAttribute('ARRAY_COUNT', 'unNumPublishedFileIDs'),
    },
    "ISteamUGC_GetQueryUGCChildren": {
        "pvecPublishedFileID": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cMaxEntries'),
    },
    "ISteamUGC_GetSubscribedItems": {
        "pvecPublishedFileID": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cMaxEntries'),
    },
    "ISteamUnifiedMessages_SendMethod": {
        "pRequestBuffer": steamworksparser.ArgAttribute('ARRAY_COUNT', 'unRequestBufferSize'),
    },
    "ISteamUnifiedMessages_GetMethodResponseData": {
        "pResponseBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'unResponseBufferSize'),
    },
    "ISteamUnifiedMessages_SendNotification": {
        "pNotificationBuffer": steamworksparser.ArgAttribute('ARRAY_COUNT', 'unNotificationBufferSize'),
    },
    "ISteamUser_InitiateGameConnection": {
        "pAuthBlob": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cbMaxAuthBlob'),
    },
    "ISteamUser_GetVoice": {
        "pDestBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbDestBufferSize'),
        "pUncompressedDestBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbUncompressedDestBufferSize'),
    },
    "ISteamUser_DecompressVoice": {
        "pCompressed": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cbCompressed'),
        "pDestBuffer": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbDestBufferSize'),
    },
    "ISteamUser_GetAuthSessionTicket": {
        "pTicket": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbMaxTicket'),
    },
    "ISteamUser_BeginAuthSession": {
        "pAuthTicket": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cbAuthTicket'),
    },
    "ISteamUser_RequestEncryptedAppTicket": {
        "pDataToInclude": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cbDataToInclude'),
    },
    "ISteamUser_GetEncryptedAppTicket": {
        "pTicket": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cbMaxTicket'),
    },
    "ISteamUserStats_GetDownloadedLeaderboardEntry": {
        "pDetails": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'cDetailsMax'),
    },
    "ISteamUserStats_UploadLeaderboardScore": {
        "pScoreDetails": steamworksparser.ArgAttribute('ARRAY_COUNT', 'cScoreDetailsCount'),
    },
    "ISteamUtils_GetImageRGBA": {
        "pubDest": steamworksparser.ArgAttribute('OUT_ARRAY_COUNT', 'nDestBufferSize'),
    },
}

g_ArgTypeDict = {
    'char *': 'string',
    'char **': 'string',
    'const char **': 'System.IntPtr',
    'uint8 *': 'byte',
    'uint16 *': 'ushort',
    'uint32 *': 'uint',
    'const uint32 *': 'uint',
    'int32 *': 'int',
    'int64 *': 'long',
    'const int32 *': 'int',
    'uint64 *': 'ulong',
    'uint64*': 'ulong',
    'const void *': 'byte',
    'void *': 'byte',
    'const SteamItemInstanceID_t *': 'SteamItemInstanceID_t',
    'const SteamItemDef_t *': 'SteamItemDef_t',
}

g_FakeArgTypesDict = {
    # This is a little nicety that we provide, I don't know why Valve doesn't just change it.
    "ISteamFriends_GetFriendCount": {
        "iFriendFlags": "EFriendFlags",
    },
    "ISteamFriends_GetFriendByIndex": {
        "iFriendFlags": "EFriendFlags",
    },
    "ISteamFriends_HasFriend": {
        "iFriendFlags": "EFriendFlags",
    },

    # These are void * but we want strings
    "ISteamFriends_GetClanChatMessage": {
        "prgchText": "char *",
    },
    "ISteamFriends_GetFriendMessage": {
        "pvData": "char *",
    },
}


# These end up being "out type", when we need them to be "ref type"
g_RefArgsDict = {
    "ISteamInventory_GetResultItems": "punOutItemsArraySize",
    "ISteamInventory_GetItemDefinitionProperty": "punValueBufferSize",
    "ISteamInventory_GetItemDefinitionIDs": "punItemDefIDsArraySize",
}

g_SkippedPtrOutArgs = (
    'const char *',
    'const char **',
    'SteamParamStringArray_t *',
    'const SteamParamStringArray_t *',
)

g_ArgTypeValuesDict = {
    # Steamworks.NET Custom
    'EFriendFlags': 'EFriendFlags.k_EFriendFlagBlocked', # No functions actually use this type, they use ints instead

    # Built in types
    'bool': 'true',
    'const char *': '"TESTSTRINGTODO:UNICODE"',
    'const char **': 'IntPtr.Zero',
    'const int32 *': 'int.MaxValue',
    'const uint32 *': 'uint.MaxValue',
    'double *': 'double.MaxValue',
    'double': 'double.MaxValue',
    'float': 'float.MaxValue',
    'int': 'int.MaxValue',
    'int32': 'int.MaxValue',
    'int64 *': 'long.MaxValue',
    'uint16': 'ushort.MaxValue',
    'uint32 *': 'uint.MaxValue',
    'uint32': 'uint.MaxValue',
    'uint64 *': 'ulong.MaxValue',
    'uint64': 'ulong.MaxValue',
    'uint8 *': 'byte.MaxValue',
    'uint8': 'byte.MaxValue',
    'unsigned int': 'uint.MaxValue',
    'unsigned short': 'ushort.MaxValue',

    'const void *': 'byte.MaxValue',
    'void *': 'byte.MaxValue',
    #'Sytstem.IntPtr': 'test',

    # Valve typedefs and structs
    'AccountID_t': '(AccountID_t)uint.MaxValue',
    'AppId_t': '(AppId_t)480',
    'CGameID': '(CGameID)ulong.MaxValue',
    'ClientUnifiedMessageHandle': '(ClientUnifiedMessageHandle)uint.MaxValue',
    'const SteamItemDef_t *': '(SteamItemDef_t)int.MaxValue',
    'const SteamItemInstanceID_t *': '(SteamItemInstanceID_t)ulong.MaxValue',
    'const SteamParamStringArray_t *': 'new string[] {"Tag One", "Tag Two", "Test Tags", "Sorry"}',
    'ControllerActionSetHandle_t': '(ControllerActionSetHandle_t)ulong.MaxValue',
    'ControllerAnalogActionHandle_t': '(ControllerAnalogActionHandle_t)ulong.MaxValue',
    'ControllerDigitalActionHandle_t': '(ControllerDigitalActionHandle_t)ulong.MaxValue',
    'ControllerHandle_t': '(ControllerHandle_t)ulong.MaxValue',
    'CSteamID *': 'new CSteamID()',
    'CSteamID': 'new CSteamID()',
    'DepotId_t': '(DepotId_t)uint.MaxValue',
    'FriendsGroupID_t': '(FriendsGroupID_t)short.MaxValue',
    'HAuthTicket': '(HAuthTicket)uint.MaxValue',
    'HHTMLBrowser': '(HHTMLBrowser)uint.MaxValue',
    'HServerListRequest': '(HServerListRequest)IntPtr.Zero',
    'HServerQuery': '(HServerQuery)int.MaxValue',
    'HSteamPipe': '(HSteamPipe)int.MaxValue',
    'HSteamUser': '(HSteamUser)int.MaxValue',
    'HTTPCookieContainerHandle': '(HTTPCookieContainerHandle)uint.MaxValue',
    'HTTPRequestHandle': '(HTTPRequestHandle)uint.MaxValue',
    'MatchMakingKeyValuePair_t **': 'new MatchMakingKeyValuePair_t { m_szKey = "TODO:UNICODE", m_szValue = "TODO:SOMEVALUE" }',
    'PublishedFileId_t *': '(PublishedFileId_t)ulong.MaxValue',
    'PublishedFileId_t': '(PublishedFileId_t)ulong.MaxValue',
    'PublishedFileId_t*': '(PublishedFileId_t)ulong.MaxValue',
    'PublishedFileUpdateHandle_t': '(PublishedFileUpdateHandle_t)ulong.MaxValue',
    'RTime32': 'uint.MaxValue',
    'ScreenshotHandle': '(ScreenshotHandle)uint.MaxValue',
    'SNetListenSocket_t': '(SNetListenSocket_t)uint.MaxValue',
    'SNetSocket_t': '(SNetSocket_t)uint.MaxValue',
    'SteamAPICall_t': 'SteamAPICall_t.Invalid',
    'SteamAPIWarningMessageHook_t': 'new SteamAPIWarningMessageHook_t((nSeverity, pchDebugText) => { Console.Write("SteamAPIWarningMessageHook_t Callback nSeverity: " + nSeverity + " pchDebugText: " + pchDebugText + "\\n"); })',
    'SteamInventoryResult_t': '(SteamInventoryResult_t)int.MaxValue',
    'SteamItemDef_t': '(SteamItemDef_t)int.MaxValue',
    'SteamItemInstanceID_t': '(SteamItemInstanceID_t)ulong.MaxValue',
    'SteamLeaderboard_t': '(SteamLeaderboard_t)ulong.MaxValue',
    'SteamLeaderboardEntries_t': '(SteamLeaderboardEntries_t)ulong.MaxValue',
    'SteamParamStringArray_t *': 'new string[] {"Tag One", "Tag Two", "Test Tags", "Sorry"}',
    'UGCFileWriteStreamHandle_t': '(UGCFileWriteStreamHandle_t)ulong.MaxValue',
    'UGCHandle_t': '(UGCHandle_t)ulong.MaxValue',
    'UGCQueryHandle_t': '(UGCQueryHandle_t)ulong.MaxValue',
    'UGCUpdateHandle_t': '(UGCUpdateHandle_t)ulong.MaxValue',

    # Enums
    'AudioPlayback_Status': 'AudioPlayback_Status.AudioPlayback_Playing',
    'EAccountType': 'EAccountType.k_EAccountTypeIndividual',
    'EGamepadTextInputLineMode': 'EGamepadTextInputLineMode.k_EGamepadTextInputLineModeMultipleLines',
    'EGamepadTextInputMode': 'EGamepadTextInputMode.k_EGamepadTextInputModePassword',
    'EHTMLKeyModifiers': 'EHTMLKeyModifiers.k_eHTMLKeyModifier_AltDown',
    'EHTMLMouseButton': 'EHTMLMouseButton.eHTMLMouseButton_Right',
    'EHTTPMethod': 'EHTTPMethod.k_EHTTPMethodGET',
    'EItemStatistic': 'EItemStatistic.k_EItemStatistic_NumFavorites',
    'ELeaderboardDataRequest': 'ELeaderboardDataRequest.k_ELeaderboardDataRequestGlobalAroundUser',
    'ELeaderboardDisplayType': 'ELeaderboardDisplayType.k_ELeaderboardDisplayTypeNumeric',
    'ELeaderboardSortMethod': 'ELeaderboardSortMethod.k_ELeaderboardSortMethodAscending',
    'ELeaderboardUploadScoreMethod': 'ELeaderboardUploadScoreMethod.k_ELeaderboardUploadScoreMethodKeepBest',
    'ELobbyComparison': 'ELobbyComparison.k_ELobbyComparisonGreaterThan',
    'ELobbyDistanceFilter': 'ELobbyDistanceFilter.k_ELobbyDistanceFilterDefault',
    'ELobbyType': 'ELobbyType.k_ELobbyTypeFriendsOnly',
    'ENotificationPosition': 'ENotificationPosition.k_EPositionTopRight',
    'EOverlayToStoreFlag': 'EOverlayToStoreFlag.k_EOverlayToStoreFlag_AddToCart',
    'EP2PSend': 'EP2PSend.k_EP2PSendUnreliableNoDelay',
    'ERemoteStoragePlatform': 'ERemoteStoragePlatform.k_ERemoteStoragePlatformWindows',
    'ERemoteStoragePublishedFileVisibility': 'ERemoteStoragePublishedFileVisibility.k_ERemoteStoragePublishedFileVisibilityFriendsOnly',
    'ESteamControllerPad': 'ESteamControllerPad.k_ESteamControllerPad_Right',
    'EUGCMatchingUGCType': 'EUGCMatchingUGCType.k_EUGCMatchingUGCType_Items_Mtx',
    'EUGCQuery': 'EUGCQuery.k_EUGCQuery_RankedByPublicationDate',
    'EUGCReadAction': 'EUGCReadAction.k_EUGCRead_ContinueReading',
    'EUserUGCList': 'EUserUGCList.k_EUserUGCList_VotedOn',
    'EUserUGCListSortOrder': 'EUserUGCListSortOrder.k_EUserUGCListSortOrder_CreationOrderAsc',
    'EWorkshopEnumerationType': 'EWorkshopEnumerationType.k_EWorkshopEnumerationTypeRecent',
    'EWorkshopFileAction': 'EWorkshopFileAction.k_EWorkshopFileActionCompleted',
    'EWorkshopFileType': 'EWorkshopFileType.k_EWorkshopFileTypeMicrotransaction',
    'EWorkshopVideoProvider': 'EWorkshopVideoProvider.k_EWorkshopVideoProviderYoutube',
}

def main(parser):
    setup_environment()

    with open('C#/Generated/test.cs', 'w') as out:
        out.write('using System;\n')
        out.write('using Steamworks;\n')
        out.write('\n')
        out.write('namespace CSteamworksTest_CS {\n')
        out.write('\tpublic static class Test {\n')
        out.write('\t\tpublic static void Run() {\n')
        out.write('\n')

        for file in parser.files:
            if file.name in g_SkippedFiles:
                continue

            if not file.interfaces:
                continue

            for interface in file.interfaces:
                out.write('\t\t\tConsole.WriteLine("' + interface.name + ' Tests:");\n')

                for func in interface.functions:
                    if func.ifstatements:
                        out.write('#if ' + func.ifstatements.replace('defined(', '').replace(')', '') + '\n')

                    if func.private:
                        continue

                    precode = []
                    printString = []
                    strNativeFuncName = interface.name + '_' + func.name
                    out.write('\t\t\t{\n')

                    funcstring = '\t\t\t\t'
                    if func.returntype != 'void':
                        funcstring += 'var ret = '
                        printString.append('" ret: " + ret + "\\n"')

                    funcstring += interface.name[1:] + '.' + func.name + '('

                    replaceArgValues = {}
                    for i, arg in enumerate(func.args):
                        argType = g_FakeArgTypesDict.get(strNativeFuncName, dict()).get(arg.name, arg.type)
                        csArgType = g_ArgTypeDict.get(argType, argType).strip('*').strip()

                        # If an arg is missing an attribute we force it in here.
                        if strNativeFuncName in g_MissingAttribsDict and arg.name in g_MissingAttribsDict[strNativeFuncName]:
                            arg.attribute = g_MissingAttribsDict[strNativeFuncName][arg.name]


                        if strNativeFuncName in g_RefArgsDict and g_RefArgsDict[strNativeFuncName] == arg.name:
                            precode.append('\t\t\t\t' + csArgType + ' ' + arg.name + ' = ' + g_ArgTypeValuesDict[argType] + ';\n')
                            funcstring += 'ref ' + arg.name
                            printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                        elif arg.name in replaceArgValues:
                            funcstring += replaceArgValues[arg.name]
                        elif arg.attribute and arg.attribute.name != 'DESC':
                            if arg.attribute.name == 'OUT_ARRAY_CONSTANT':
                                precode.append('\t\t\t\tvar ' + arg.name + ' = new ' + csArgType + '[Constants.' + arg.attribute.value + '];\n')
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                            elif arg.attribute.name == 'OUT_ARRAY_COUNT':
                                precode.append('\t\t\t\tvar ' + arg.name + ' = new ' + csArgType + '[8];\n')
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))

                                replaceArgValues[arg.attribute.value.split(',')[0]] = '8'
                            elif arg.attribute.name == 'OUT_ARRAY_CALL':
                                precode.append('\t\t\t\tvar ' + arg.name + ' = new ' + csArgType + '[8];\n')
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))

                                replaceArgValues[arg.attribute.value.split(',')[0]] = '8'
                            elif arg.attribute.name == 'ARRAY_COUNT' or arg.attribute.name == 'ARRAY_COUNT_D':
                                precode.append('\t\t\t\t{0}[] {1} = {{ {2}, {2} }};\n'.format(csArgType, arg.name, g_ArgTypeValuesDict[argType]))
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))

                                replaceArgValues[arg.attribute.value.split(',')[0]] = '2'
                            elif arg.attribute.name == 'OUT_STRING':
                                precode.append('\t\t\t\t' + csArgType + ' ' + arg.name + ';\n')
                                funcstring += 'out ' + arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                            elif arg.attribute.name == 'OUT_STRING_COUNT':
                                precode.append('\t\t\t\t' + csArgType + ' ' + arg.name + ';\n')
                                funcstring += 'out ' + arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                            elif arg.attribute.name == 'OUT_STRUCT':
                                precode.append('\t\t\t\t' + csArgType + ' ' + arg.name + ';\n')
                                funcstring += 'out ' + arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                            elif arg.attribute.name == 'OUT_BUFFER_COUNT':
                                precode.append('\t\t\t\tvar ' + arg.name + ' = new ' + csArgType + '[8];\n')
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))

                                #replaceArgValues[arg.attribute.value.split(',')[0]] = '8'
                            elif arg.attribute.name == 'BUFFER_COUNT':
                                precode.append('\t\t\t\t{0}[] {1} = {{ {2}, {2} }};\n'.format(csArgType, arg.name, g_ArgTypeValuesDict[argType]))
                                funcstring += arg.name
                                printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))

                                replaceArgValues[arg.attribute.value.split(',')[0]] = '2'
                            else:
                                print(interface.name + '_' + func.name + ' ' + arg.name + ': ' + arg.attribute.name)
                        elif argType.endswith('*') and arg.type not in g_SkippedPtrOutArgs:
                            precode.append('\t\t\t\t' + csArgType + ' ' + arg.name + ';\n')
                            funcstring += 'out ' + arg.name
                            printString.append('" {0}: " + {0} + "\\n"'.format(arg.name))
                        elif argType in g_ArgTypeValuesDict:
                            funcstring += g_ArgTypeValuesDict[argType]
                        else:
                            print(strNativeFuncName + ' is broken on arg: ' + arg.name + ' with type: ' + argType)
                        
                        if i != len(func.args) - 1:
                            funcstring += ', '

                    funcstring += ');\n'

                    for line in precode:
                        out.write(line)

                    out.write(funcstring)
                    if printString:
                        out.write('\t\t\t\tConsole.Write(')
                        for j, line in enumerate(printString):
                            out.write(line)

                            if j != len(printString) - 1:
                                out.write(' + ')

                        out.write(');\n')

                    out.write('\t\t\t}\n')
                    if func.ifstatements:
                        out.write('#endif\n')

                out.write('\n')

        out.write('\t\t}\n')
        out.write('\t}\n')
        out.write('}\n')

def setup_environment():
    try:
        os.makedirs('C#/Generated/')
    except OSError:
        pass

    try:
        os.makedirs('C#/Steamworks.NET/')
    except OSError:
        pass

    copyfile('../Steamworks.NET/Steamworks.NET/Standalone/bin/x86/Windows/Steamworks.NET.dll', 'C#/Steamworks.NET/Steamworks.NET.dll') # TODO: Hardcoded Path

if __name__ == '__main__':
    #steamworksparser.Settings.fake_gameserver_interfaces = True
    main(steamworksparser.parse('..\\CSteamworks\\steam')) # TODO: Hardcoded Path
