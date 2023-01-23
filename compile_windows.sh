#!/bin/bash
echo -e "[+] Compile CGSC"
cmake --build src/CGSC/build

echo -e "[+] Compile SR"
cmake --build src/SR/build

echo -e "[+] Compile CoD4x"
mingw32-make

echo -e "[+] Copy Binary"
cp -v bin/cod4x18_dedrun.exe "/d/Program Files (x86)/Activision/Cod4Mod"
