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
copy /v bin\cod4x18_dedrun.exe "C:\Program Files (x86)\Activision\CoD4Mod"
copy /v bin\gsclib.dll "C:\Program Files (x86)\Activision\CoD4Mod\plugins"
