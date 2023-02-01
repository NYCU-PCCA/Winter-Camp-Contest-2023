#!/bin/bash
export XDG_CONFIG_HOME=$PWD
# TODO: p2d https://github.com/cn-xcpc-tools/testlib-for-domjudge/tree/master/p2d
# https://github.com/cubercsl/polygon2domjudge
p2d.sh problems
mkdir gen
mv *.zip gen
