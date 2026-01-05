#!/bin/bash

# SR
echo -e "[+] SR"
cmake --build src/SR/build --target install

# CoD4x
echo -e "[+] CoD4x"
rm bin/cod4x18_dedrun
make

# gsclib
echo -e "[+] gsclib"
cmake --build plugins/gsclib/build --target install

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
cp -v bin/gsclib.so /home/cod4/plugins
