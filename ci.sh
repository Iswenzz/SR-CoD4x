#!/bin/bash
ROOT="$(pwd)"

# CGSC
echo -e "[+] CGSC"
cd src/CGSC
rm -r build
mkdir build
cd build
cmake .. --preset linux
cmake --build .
cd $ROOT

# SR
echo -e "[+] SR"
cd src/SR
rm -r build
mkdir build
cd build
cmake .. --preset linux
cmake --build .
cd $ROOT

# CoD4x
echo -e "[+] CoD4x"
make
