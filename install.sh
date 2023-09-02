#!/bin/bash
ROOT="$(pwd)"
CONAN=--profile $ROOT/.conan/linux.conf --build missing -s compiler.version=11

# Dependencies
echo -e "[+] Dependencies"
conan create deps/speex $CONAN

# CoD4DM1
echo -e "[+] CoD4DM1"
cd deps/CoD4DM1
conan create . $CONAN
mkdir build
cd build
conan install .. $CONAN
cmake ..
cmake --build .
cp -v lib/libCoD4DM1.a $ROOT/lib
cd $ROOT

# CGSC
echo -e "[+] CGSC"
cd src/CGSC
conan create . $CONAN
mkdir build
cd build
conan install .. $CONAN
cmake ..
cmake --build .
cd $ROOT

# SR
echo -e "[+] SR"
cd src/SR
mkdir build
cd build
conan install .. $CONAN
cmake ..
cmake --build .
cd $ROOT

# CoD4x
echo -e "[+] CoD4x"
make

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
