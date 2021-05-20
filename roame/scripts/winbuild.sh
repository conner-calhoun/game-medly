#!/usr/bin/env bash

TL=$(dirname $(readlink -f $BASH_SOURCE))/..
BD=$TL/build

if [[ $1 == "c" ]]; then
    rm -rf $BD
fi

if [[ ! -d $BD ]]; then
    mkdir $BD
fi

pushd $BD
cmake ..
cmake --build .

# copy dlls
if [[ $? == 0 ]]; then
    cp $TL/lib/Runtime/*/*.dll $BD/Debug
fi
popd
