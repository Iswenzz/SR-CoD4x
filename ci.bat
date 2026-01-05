@echo off
set ROOT="%cd%"
set CC=gcc
set CXX=g++

:: SR
echo [+] SR
cd src\sr
mkdir build
cd build
cmake .. --preset windows
cmake --build . --target install
cd %ROOT%

:: CoD4x
echo [+] CoD4x
mingw32-make
