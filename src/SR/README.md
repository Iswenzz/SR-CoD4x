# SR-CoD4x

[![Checks](https://img.shields.io/github/checks-status/Iswenzz/SR-CoD4x/master?logo=github)](https://github.com/Iswenzz/SR-CoD4x/actions)
[![License](https://img.shields.io/github/license/Iswenzz/SR-CoD4x?color=blue&logo=gitbook&logoColor=white)](https://github.com/Iswenzz/SR-CoD4x/blob/master/LICENSE)

## Building (Linux)
_Pre-Requisites:_

	sudo dpkg --add-architecture i386
	sudo apt-get update
	sudo apt-get install nasm:i386 build-essential gcc-multilib g++-multilib

_Build Command:_

    mkdir build && cd build
    conan install .. --build missing --profile ../.conan/linux.conf
    cmake ..
    cmake --build .

## Building (Windows)
_Pre-Requisites:_
1. Windows [MinGW-W64 8.1.0 i686 Win32 dwarf](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-win32/dwarf/i686-8.1.0-release-win32-dwarf-rt_v6-rev0.7z)
2. [NASM](https://www.nasm.us/)
3. [CMake](https://cmake.org/) and [Conan](https://conan.io/).

_Build Command:_

    mkdir build && cd build
    conan install .. --build missing --profile ../.conan/windows.conf
    cmake .. -G "MinGW Makefiles"
    cmake --build .

## Contributors:
***Note:*** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.
