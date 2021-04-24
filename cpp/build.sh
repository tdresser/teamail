#!/bin/bash

cd `dirname $0`

mkdir -p ../web/build

emcmake cmake -B out -GNinja
emmake ninja -C out

cp out/bin/Main.js ../web/build/
cp out/bin/Main.wasm ../web/build/