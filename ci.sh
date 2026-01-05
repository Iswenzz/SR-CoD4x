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
make
