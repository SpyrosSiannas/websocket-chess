#!/usr/bin/bash

if [[ $1 == "-r" ]]; then
    echo "Rebuilding"
    rm -rf build
fi

if [ ! -d build ]; then
    mkdir build
fi

cd build 
cmake ..
make
