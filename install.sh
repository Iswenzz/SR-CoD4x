#!/bin/bash
ROOT="$(pwd)"

# CGSC
echo -e "[+] CGSC"
cd src/CGSC
rm -r build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=.vcpkg/linux.cmake -DCOD4X=True
cmake --build .
cd $ROOT

# SR
echo -e "[+] SR"
cd src/SR
rm -r build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=.vcpkg/linux.cmake
cmake --build .
cd $ROOT

# CoD4x
echo -e "[+] CoD4x"
make

# gsclib
echo -e "[+] gsclib"
cd plugins/gsclib
rm -r build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=.vcpkg/linux.cmake
cmake --build .
cd $ROOT

# Binary
echo -e "[+] Binary"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
