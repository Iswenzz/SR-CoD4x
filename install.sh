#!/bin/bash
ROOT="$(pwd)"
CC=gcc
CXX=g++

# Clean
echo -e "[+] Clean"
make clean
rm bin/cod4x18_dedrun
rm bin/gsclib.so
rm -r src/sr/build
rm -r plugins/gsclib/build

# API
echo -e "[+] API"
cd plugins/gsclib/api
./install.sh
cd $ROOT

# SR
echo -e "[+] SR"
cd src/sr
mkdir build
cd build
cmake .. --preset linux
cmake --build . --target install
cd $ROOT

# CoD4x
echo -e "[+] CoD4x"
make

# gsclib
echo -e "[+] gsclib"
cd plugins/gsclib
mkdir build
cd build
cmake .. --preset linux
cmake --build .
cd $ROOT

# Install
echo -e "[+] Install"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
cp -v bin/gsclib.so /home/cod4/plugins
