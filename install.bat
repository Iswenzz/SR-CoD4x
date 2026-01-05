@echo off
set ROOT="%cd%"
set CC=gcc
set CXX=g++

:: Clean
echo [+] Clean
mingw32-make clean
del bin\cod4x18_dedrun.exe
del bin\gsclib.dll
rmdir /s /q src\sr\build
rmdir /s /q plugins\gsclib\build

:: API
echo [+] API
cd plugins\gsclib\api
call install.bat
cd %ROOT%

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

:: gsclib
echo [+] gsclib
cd plugins\gsclib
mkdir build
cd build
cmake .. --preset windows
cmake --build .
cd %ROOT%

:: Install
echo [+] Install
copy /v bin\cod4x18_dedrun.exe "D:\Dev\CoD4\SDK"
copy /v bin\gsclib.dll "D:\Dev\CoD4\SDK\plugins"
