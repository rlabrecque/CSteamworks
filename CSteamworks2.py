#!/usr/bin/env python3
import os
from SteamworksParser import steamworksparser

CPP_HEADER = "// This file is automatically generated!\n\n"

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


def main():
    entrypoints = []
    cppfilenames = []

    try:
        os.makedirs("wrapper/")
    except OSError:
        pass

    with open("wrapper/steam_api_c.h", "w") as header:
        header.write(CPP_HEADER)
        header.write("#pragma once\n\n")
        header.write("#include \"CSteamworks.h\"\n\n")

    #steamworksparser.Settings.warn_utf8bom = True
    #steamworksparser.Settings.warn_includeguardname = True
    #steamworksparser.Settings.print_unuseddefines = True
    steamworksparser.Settings.fake_gameserver_interfaces = True
    parser = steamworksparser.parse("steam/")

    for f in parser.files:
        if f.name in g_SkippedFiles:
            continue

        print("File: " + f.name)
        if not f.interfaces:
            continue

        with open("wrapper/" + os.path.splitext(f.name)[0] + ".cpp", "w") as out, open ("wrapper/steam_api_c.h", "a") as header:
            out.write(CPP_HEADER)
            cppfilenames.append(os.path.splitext(f.name)[0] + ".cpp")

            lastIfBlock = None
            for i in f.interfaces:
                print(" - " + i.name)
                for func in i.functions:
                    if lastIfBlock is not None and lastIfBlock != func.ifstatements:
                        out.write("#endif\n")
                        lastIfBlock = None

                    if func.ifstatements and func.ifstatements != lastIfBlock:
                        out.write("#if " + func.ifstatements + "\n")
                        lastIfBlock = func.ifstatements

                    if func.private:
                        continue

                    def create_arg_string(arg):
                        argtype = g_TypeDict.get(arg.type, arg.type)
                        space = "" if argtype.endswith("*") and " " in argtype else " "
                        defaultarg = "" if not arg.default else " = " + arg.default
                        return argtype + space + arg.name + defaultarg

                    args = ", ".join([create_arg_string(arg) for arg in func.args])
                    argnames = ", ".join([arg.name for arg in func.args])
                    '''for arg in func.args:
                        argtype = g_TypeDict.get(arg.type, arg.type)

                        spaceHACK = " "
                        if argtype.endswith("*") and " " in argtype:
                            spaceHACK = ""  # TODO: REMOVE THIS HACK
                        args += argtype + spaceHACK + arg.name
                        if arg.default:
                            args += " = " + arg.default
                        args += ", "
                    args = args[:-2]'''

                    returntype = func.returntype
                    ConvertToUint64 = ""
                    if returntype == "CSteamID":
                        returntype = "SteamID_t"
                        ConvertToUint64 = ".ConvertToUint64()"

                    # If a function overrides another with the same name but different args, we fix it up here so that it can be properly exposed.
                    strEntryPoint = i.name + "_" + func.name
                    if strEntryPoint in entrypoints:
                        strEntryPoint += "_"
                    entrypoints.append(strEntryPoint)

                    declaration = "SB_API " + returntype + " S_CALLTYPE " + strEntryPoint + "(" + args + ")"
                    header.write(declaration + ";\n")
                    out.write(declaration + " {\n")
                    out.write("\treturn " + i.name[1:] + "()->" + func.name + "(" + argnames + ")" + ConvertToUint64 + ";\n")
                    out.write("}\n")
                    out.write("\n")

            if lastIfBlock:
                out.write("#endif\n")

    if cppfilenames:
        with open("wrapper/unitybuild.cpp", "w") as out:
            out.write(CPP_HEADER)
            for filename in cppfilenames:
                out.write("#include \"" + filename + "\"\n")

if __name__ == "__main__":
    main()
