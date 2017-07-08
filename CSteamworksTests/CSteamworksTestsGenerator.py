#!/bin/env/python
import os
import sys
from SteamworksParser import steamworksparser

g_SkippedFiles = (
    # We don't currently support the following interfaces because they don't provide a factory of their own.
    # You are expected to call GetISteamGeneric to get them.
    "isteamappticket.h",
    "isteamgamecoordinator.h",
    # PS3 is not supported.
    "isteamps3overlayrenderer.h",
)


g_TypeDict = {
    'EHTMLMouseButton': 'ISteamHTMLSurface::EHTMLMouseButton',
    'EHTMLKeyModifiers': 'ISteamHTMLSurface::EHTMLKeyModifiers',
}

g_ArgTypeDict = {
    "bool": "true",
    "SteamAPIWarningMessageHook_t": "NULL",
    "SteamAPI_PostAPIResultInProcess_t": "NULL",
    "SteamAPI_CheckCallbackRegistered_t": "NULL",
    "HServerListRequest": "NULL",
    "AudioPlayback_Status": "(AudioPlayback_Status)0",
    "CSteamID": "76561197991230424ull",
    "CGameID": "CGameID(21212)",
    "const char *": '"TESTING123"',
}

g_TypePreamble = {
    "AppId_t *": ''
}

def main(parser):
    try:
        os.makedirs("C/Generated/")
    except OSError:
        pass

    with open("C/Generated/tests.h", "w") as out:
        out.write("#pragma once\n\n")
        out.write("void RunTests();")

    with open("C/Generated/test.cpp", "w") as out:
        out.write('#include "tests.h"\n')
        out.write('typedef unsigned long long uint64_t;\n')
        out.write('#include "steam_api_c.h"\n')
        out.write("#include <iostream>\n")
        out.write("using namespace std;\n")
        out.write("\n")
        out.write("void RunTests() {\n")
        out.write('\tvoid* buffer[8192] = {0};\n')
        out.write('\n')

        entrypoints = []
        for f in parser.files:
            if f.name in g_SkippedFiles:
                continue

            if not f.interfaces:
                continue

            lastIfBlock = None
            for i in f.interfaces:
                out.write('\tcout << "' + i.name + ' Tests:\\n";\n')

                for func in i.functions:

                    if lastIfBlock is not None and lastIfBlock != func.ifstatements:
                        out.write("#endif\n")
                        lastIfBlock = None

                    if func.ifstatements and func.ifstatements != lastIfBlock:
                        out.write("#if " + func.ifstatements + "\n")
                        lastIfBlock = func.ifstatements

                    strEntryPoint = i.name + "_" + func.name
                    if strEntryPoint in entrypoints:
                        strEntryPoint += "_"
                    entrypoints.append(strEntryPoint)

                    args = ''
                    preamble = ""
                    outparams = "<<"
                    for arg in func.args:
                        argtype = g_TypeDict.get(arg.type, arg.type)
                        if argtype in g_ArgTypeDict:
                            args += g_ArgTypeDict[argtype]
                        elif argtype in g_TypePreamble:
                            val = g_TypePreamble[argtype]
                            preamble += '\t\t' + argtype + arg.name
                            if val:
                                preamble += ' = ' + val
                            preamble += ';\n'
                            args += arg.name
                        elif argtype.endswith("*"):
                            args +=  '(' + argtype + ')&buffer'
                        elif arg.type.startswith("E"):
                            args += "(" + argtype + ")0"
                        else:
                            args += "21212"

                        args += ', '


                    else:
                        args = args[:-2]

                    if func.returntype == "void":
                        out.write('\t' + strEntryPoint + '(' + args + ');\n')
                    else:
                        out.write('\t{\n')
                        if preamble:
                            out.write(preamble)
                        out.write('\t\tauto ret = ' + strEntryPoint + '(' + args + ');\n')
                        out.write('\t\tcout << " ret: " << ret ' + outparams + ' "\\n";\n')
                        out.write('\t}\n')

                if lastIfBlock:
                    out.write("#endif\n")
                    lastIfBlock = None

                out.write("\n")

        out.write("}\n")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("TODO: Usage Instructions")
        exit()

    steamworksparser.Settings.fake_gameserver_interfaces = True
    main(steamworksparser.parse(sys.argv[1]))
