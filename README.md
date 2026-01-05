# SR CoD4x

CoD4x is a modification of the Call of Duty 4 - Modern Warfare server. It fixes several bugs in the original binaries and allows developers to extend server functionality with additional variables and plugins. When using the CoD4x server, the clients invoke installation of the proprietary CoD4x client to players joining the server using the CoD4x servers, which fixes several known base game bugs in the client, and in combination with the server allows for extra features.

# SR Features
* gsclib standard library
* Extended player movements
* Increased assets pool
* Record demos
* FPS calculation
* Demo player
* Netcode optimization
* Voice chat proximity feature
* Radio MP3 & WAV streaming

## CoD4x Features
* Administration commands
* Measurements against hackers
* Reliable player identification
* Pbss like screenshot feature
* Automated client update, no manual installation needed
* Backwards compatibility to 1.7 and 1.7a servers
* A new [masterserver](http://cod4master.cod4x.ovh/), for when the official masterserver is down

## Setting up a server
You also require the base game to run a server. Copy every .iwd file in `cod4directory/main/` to `serverdirectory/main/`.
Also copy everything inside `cod4directory/zone` to `serverdirectory/zone`.

Now you can run the server with `./cod4x18_dedrun +map mp_killhouse`. If you are running a local server on Windows use `cod4x18_dedrun.exe +map mp_killhouse +set dedicated 2 +set net_ip 127.0.0.1`. Join the server with your client via the console (`^`) by typing `/connect 127.0.0.1` (if hosted locally), and see if you can join the server.

A more detailed server tutorial is available on [our wiki](https://github.com/callofduty4x/CoD4x_Server/wiki/Server-setup).

## Building (Windows)

_Pre-Requisites:_

1. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/).

_Build Command:_

    mkdir build && cd build
    cmake .. --preset windows
    cmake --build . --target install

## Building (Linux)

_Pre-Requisites:_

1. [CMake](https://cmake.org/) and [vcpkg](https://vcpkg.io/en/).

	sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install build-essential gcc-multilib g++-multilib pkg-config linux-libc-dev nasm:i386

_Build Command:_

    mkdir build && cd build
    cmake .. --preset linux
    cmake --build . --target install

## [Download](https://github.com/Iswenzz/gsclib/releases)

## Contributors:

**_Note:_** If you would like to contribute to this repository, feel free to send a pull request, and I will review your code. Also feel free to post about any problems that may arise in the issues section of the repository.

