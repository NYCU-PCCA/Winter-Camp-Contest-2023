#!/bin/bash
docker run --rm \
  -v "$PWD":/data -w /data \
  -p 12345:8888 openjdk:11 \
  java -jar live-v3-9dad482.jar \
    -port=8888 \
    -P:live.configDirectory=config
