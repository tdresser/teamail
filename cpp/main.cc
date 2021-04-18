#include <emscripten.h>
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE 
extern "C" int main() {
    printf("It worked!! \\o/\n");
    return 7;
}