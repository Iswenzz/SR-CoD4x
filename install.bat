@echo off
set ROOT="%cd%"
set CC=gcc
set CXX=g++

:: CGSC
echo [+] CGSC
cd src/CGSC
rmdir build /s /q
mkdir build
cd build
cmake .. --preset windows
cmake --build .
cd %ROOT%

:: SR
echo [+] SR
cd src/SR
rmdir build /s /q
mkdir build
cd build
cmake .. --preset windows
cmake --build .
cd %ROOT%

:: CoD4x
echo [+] CoD4x
del bin\cod4x18_dedrun.exe
mingw32-make clean
mingw32-make

:: gsclib
echo [+] gsclib
cd plugins/gsclib
rmdir build /s /q
mkdir build
cd build
cmake .. --preset windows
cmake --build .
cd %ROOT%

:: Binary
echo [+] Binary
copy /v bin\cod4x18_dedrun.exe "D:\Dev\CoD4\SDK"
copy /v bin\gsclib.dll "D:\Dev\CoD4\SDK\plugins"
