#!/bin/bash
export XDG_CONFIG_HOME=$PWD
p2d.sh problems
mkdir gen
mv *.zip gen
