#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE 
extern "C" int test() {
    return 5;
}