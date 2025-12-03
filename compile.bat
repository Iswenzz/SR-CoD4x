@echo off
set CC=gcc
set CXX=g++

:: CGSC
echo [+] CGSC
cmake --build src/CGSC/build

:: SR
echo [+] SR
cmake --build src/SR/build

:: CoD4x
echo [+] CoD4x
del bin\cod4x18_dedrun.exe
mingw32-make

:: gsclib
echo [+] gsclib
cmake --build plugins/gsclib/build

:: Binary
echo [+] Binary
copy /v bin\cod4x18_dedrun.exe "D:\Dev\CoD4\SDK"
copy /v bin\gsclib.dll "D:\Dev\CoD4\SDK\plugins"
