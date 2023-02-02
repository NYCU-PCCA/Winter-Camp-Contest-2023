#!/bin/bash
set -x
export ICPC_FONT='Noto Sans CJK'
source ./env
cd ./resolver-2.5.871
./awards.sh
./resolver.sh $URL $USER $PASS --presenter --display 2
