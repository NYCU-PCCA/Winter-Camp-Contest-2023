#!/bin/bash
set -xe
mkdir -p gen
for f in ../problem/*; do
  p=${f##*/}
  cd "../problem/$p"
  zip -r "../../prepare/gen/$p.zip" . "$@"
  cd "$OLDPWD"
done
