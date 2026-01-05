#!/bin/bash
ROOT="$(pwd)"
CC=gcc
CXX=g++

# API
echo -e "[+] API"
cd plugins/gsclib/api
./install.sh
cd $ROOT

# SR
echo -e "[+] SR"
cmake --build src/sr/build --target install

# CoD4x
echo -e "[+] CoD4x"
make

# gsclib
echo -e "[+] gsclib"
cmake --build plugins/gsclib/build

# Install
echo -e "[+] Install"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
cp -v bin/gsclib.so /home/cod4/plugins
