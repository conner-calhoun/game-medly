#!/usr/bin/env bash

TL=$(dirname $(readlink -f $BASH_SOURCE))/..

cd $TL

if [[ ! -d deps ]]; then
    mkdir deps
fi

cd deps

git clone https://github.com/ocornut/imgui.git
git clone https://github.com/glfw/glfw.git
