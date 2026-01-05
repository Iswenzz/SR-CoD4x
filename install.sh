#!/bin/bash
ROOT="$(pwd)"

# SR
echo -e "[+] SR"
cd src/SR
rm -r build
mkdir build
cd build
cmake .. --preset linux
cmake --build . --target install
cd $ROOT

# CoD4x
echo -e "[+] CoD4x"
rm bin/cod4x18_dedrun
make clean
make

# gsclib
echo -e "[+] gsclib"
cd plugins/gsclib
rm -r build
mkdir build
cd build
cmake .. --preset linux
cmake --build . --target install
cd $ROOT

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
cp -v bin/gsclib.so /home/cod4/plugins
