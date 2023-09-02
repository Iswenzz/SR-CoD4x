#!/bin/bash

# CGSC
echo -e "[+] CGSC"
cmake --build src/CGSC/build

# SR
echo -e "[+] SR"
cmake --build src/SR/build

# CoD4x
echo -e "[+] CoD4x"
make

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
