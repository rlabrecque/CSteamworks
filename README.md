CSteamworks
=======

_CSteamworks_ is a C ABI Wrapper for Valve's Steamworks API. It relys heavily on automatic code generation.
The primary use case for CSteamworks is to act as a buffer between a scripting language and C++ Interfaces.

* Author: [Riley Labrecque](https://github.com/rlabrecque)
* License: [MIT](http://www.opensource.org/licenses/mit-license.php)
* [Github Project](https://github.com/rlabrecque/CSteamworks)
* [Reporting Issues](https://github.com/rlabrecque/CSteamworks/issues)
* Currently supports Steamworks SDK v1.25

[![Support via Gittip](https://rawgithub.com/twolfson/gittip-badge/0.1.0/dist/gittip.png)](https://www.gittip.com/rlabrecque/)

Building
--------

To use CSteamworks you must be a Steamworks developer.

* Download the Latest Steamworks SDK from the Steamworks Partner site.
* Copy 'redistibutable_bin/' over from the Steamworks SDK into the root of this folder.
* Copy the 'steam/' folder located in 'public/' over from the Steamworks SDK into the root of this folder.
* Run CSteamworks.py which will generate the wrapper files into 'wrapper/'
* Use the Makefile/Project files in 'build/' to compile your dynamic library.

Limitations
-----------

* CSteamworks was not intended to be used directly from C/C++ therefore it does not provide header files.
* CSteamworks does not currently support ISteamAppTicket or ISteamGameCoordinator
