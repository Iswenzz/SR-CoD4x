@echo off
set ROOT="%cd%"

:: CGSC
echo [+] CGSC
cd src/CGSC
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=.vcpkg/windows.cmake -DCOD4X=True
cmake --build .
cd %ROOT%

:: SR
echo [+] SR
cd src/SR
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=.vcpkg/windows.cmake
cmake --build .
cd %ROOT%

:: CoD4x
echo [+] CoD4x
mingw32-make

:: Binary
echo [+] Binary
copy /v bin\cod4x18_dedrun.exe "D:\Program Files (x86)\Activision\Cod4Mod"
