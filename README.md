# teamail

## Setup

### Once

git submodule init
deps/emsdk/emsdk install latest
deps/emsdk/emsdk activate latest

For wasm debugging, make sure to set up the extension.
For WSL, Tim uses.
/home/tim/ \\wsl$\Ubuntu\home\tim\

To get clangd working with emscripten, you'll probably need:
`sudo apt-get install libc6-dev-i386`
Maybe also `libc6-dev-i386-cross`? Or
`sudo apt-get install gcc-multilib g++-multilib`

### Repeatedly

source deps/emsdk/emsdk_env.sh

# Notes

There's a static assert in emscripten which I've just removed, which is gross. TODO
