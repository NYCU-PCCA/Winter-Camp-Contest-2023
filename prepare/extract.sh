#!/bin/bash
for f in gen/*.zip; do
  f=${f##*/}
  p=${f%.*}
  d=../problem/$p
  rm -fr "$d"
  unzip "gen/$p.zip" -d "$d"
done
