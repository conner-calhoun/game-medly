#!/usr/bin/env bash

## Source this file to get aliases and stuff

PROJ_DIR=$(dirname $(readlink -f $BASH_SOURCE))/..
alias br="$PROJ_DIR/scripts/winbuild.sh && $PROJ_DIR/scripts/run.sh"