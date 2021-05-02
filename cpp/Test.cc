#include <emscripten/bind.h>

extern "C" int test() {
  return 50000;
}

EMSCRIPTEN_BINDINGS(test) {
  emscripten::function("test", &test);
}
