@echo off
set ROOT="%cd%"
set CC=gcc
set CXX=g++

:: API
echo [+] API
cd plugins\gsclib\api
call install.bat
cd %ROOT%

:: SR
echo [+] SR
cmake --build src\sr\build --target install

:: CoD4x
echo [+] CoD4x
del bin\cod4x18_dedrun.exe
mingw32-make

:: gsclib
echo [+] gsclib
cmake --build plugins\gsclib\build

:: Install
echo [+] Install
copy /v bin\cod4x18_dedrun.exe "D:\Dev\CoD4\SDK"
copy /v bin\gsclib.dll "D:\Dev\CoD4\SDK\plugins"
