@echo off
set ROOT="%cd%"

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
