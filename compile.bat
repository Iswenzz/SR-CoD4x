@echo off

:: CGSC
echo [+] CGSC
cmake --build src/CGSC/build

:: SR
echo [+] SR
cmake --build src/SR/build

:: CoD4x
echo [+] CoD4x
mingw32-make

:: gsclib
echo [+] gsclib
cmake --build plugins/gsclib/build

:: Binary
echo [+] Binary
copy /v bin\cod4x18_dedrun.exe "D:\Program Files (x86)\Activision\Cod4Mod"
