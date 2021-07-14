#!/usr/bin/env bash

TL=$(dirname $(readlink -f $BASH_SOURCE))/..
cd $TL

if [[ ! -d build ]]; then
    echo "No build available to run"
    return -1
fi

cd build/Debug && ./test_Kafei.exe