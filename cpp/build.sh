#!/bin/bash

cd `dirname $0`

if [[ $1 ]]; then
  TARGET=$1
else
  TARGET=`cat default_build.txt`
fi

echo $TARGET

case $TARGET in
  Test)
    mkdir -p out_test
    cmake -DBUILD=Test -GNinja -B out_test && \
    ninja -C out_test Test
  ;;
  Web)
    mkdir -p ../web/build
    mkdir -p out_web

    emcmake cmake -DBUILD=Web -GNinja -B out_web && \
    emmake ninja -C out_web Web

    cp out_web/bin/Web.js ../web/build/
    cp out_web/bin/Web.wasm ../web/build/
  ;;
  *)
    echo "Please provide a supported target (web or test)."
esac



