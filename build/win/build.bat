call "%VS100COMNTOOLS%vsvars32.bat"

msbuild CSteamworks.sln /t:build /p:Configuration=Release;Platform=Win32
msbuild CSteamworks.sln /t:build /p:Configuration=Release;Platform=x64