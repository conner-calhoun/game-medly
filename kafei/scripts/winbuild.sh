#!/usr/bin/env bash

TL=$(dirname $(readlink -f $BASH_SOURCE))/..
cd $TL

if [[ ! -d build ]]; then
    mkdir build
fi

cd build
cmake ..

if [[ $1 == "-r " ]]; then
    config="/property:Configuration=Release"
fi

MSBuild.exe kafei.sln $config
