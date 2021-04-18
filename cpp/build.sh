#!/bin/bash

emcmake cmake -B out -GNinja
emmake ninja -C out
cp out/bin/Main.js ../web/teamail/public/
cp out/bin/Main.wasm ../web/teamail/public/