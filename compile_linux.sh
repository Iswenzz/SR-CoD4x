#!/bin/bash
echo -e "[+] Compile CGSC"
cmake --build src/CGSC/build

echo -e "[+] Compile SR"
cmake --build src/SR/build

echo -e "[+] Compile CoD4x"
make

echo -e "[+] Copy Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
