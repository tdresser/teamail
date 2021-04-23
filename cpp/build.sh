#!/bin/bash

cd "$( dirname "${BASH_SOURCE[0]}" )"

emcmake cmake -B out -GNinja
emmake ninja -C out
cp out/bin/Main.js ../web/teamail/build/
cp out/bin/Main.wasm ../web/teamail/build/