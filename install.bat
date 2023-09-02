@echo off
set ROOT="%cd%"
set CONAN=--profile %ROOT%/.conan/windows.conf --build missing -s compiler.version=13

:: Dependencies
echo [+] Dependencies
conan create deps/speex %CONAN%

:: CoD4DM1
echo [+] CoD4DM1
cd deps/CoD4DM1
conan create . %CONAN%
mkdir build
cd build
conan install .. %CONAN%
cmake .. -G "MinGW Makefiles"
cmake --build .
copy /v lib\libCoD4DM1.a %ROOT%\lib\libCoD4DM1.a
cd %ROOT%

:: CGSC
echo [+] CGSC
cd src/CGSC
conan create . %CONAN%
mkdir build
cd build
conan install .. %CONAN%
cmake .. -G "MinGW Makefiles"
cmake --build .
cd %ROOT%

:: SR
echo [+] SR
cd src/SR
mkdir build
cd build
conan install .. %CONAN%
cmake .. -G "MinGW Makefiles"
cmake --build .
cd %ROOT%

:: CoD4x
echo [+] CoD4x
mingw32-make

:: Binary
echo [+] Binary
copy /v bin\cod4x18_dedrun.exe "D:\Program Files (x86)\Activision\Cod4Mod"
