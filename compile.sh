#!/bin/bash

# CGSC
echo -e "[+] CGSC"
cmake --build src/CGSC/build

# SR
echo -e "[+] SR"
cmake --build src/SR/build

# CoD4x
echo -e "[+] CoD4x"
rm bin/cod4x18_dedrun
make

# gsclib
echo -e "[+] gsclib"
cmake --build plugins/gsclib/build

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
cp -v bin/gsclib.so /home/cod4/plugins
