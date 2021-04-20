#!/bin/bash

emcmake cmake -B out -GNinja
emmake ninja -C out
cp out/bin/Main.js ../web/teamail/src/Main.mjs
cp out/bin/Main.wasm ../web/teamail/src/