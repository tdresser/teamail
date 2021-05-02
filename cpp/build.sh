#!/bin/bash

cd `dirname $0`

if [[ $1 ]]; then
  TARGET=$1
else
  TARGET=`cat default_build.txt`
fi

case $TARGET in 
  Test) 
    mkdir -p out_test
    cmake -GNinja -S . -B out_test && \
    ninja -C out_test Lib
  ;;
  Web)
    mkdir -p ../web/build
    mkdir -p out_web

    emcmake cmake -GNinja -S . -B out_web && \
    emmake ninja -C out_web Web

    cp out_web/bin/Main.js ../web/build/
    cp out_web/bin/Main.wasm ../web/build/
  ;;
  *)
    echo "Please provide a supported target (web or test)."
esac



