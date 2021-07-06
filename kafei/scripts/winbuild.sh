#!/usr/bin/env bash

TL=$(dirname $(readlink -f $BASH_SOURCE))/..
cd $TL

if [[ ! -d build ]]; then
    mkdir build
fi

cd build
cmake ..
MSBuild.exe kafei.sln