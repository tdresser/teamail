#include <emscripten/bind.h>
using namespace emscripten;

extern "C" int test()
{
    return 50;
}

EMSCRIPTEN_BINDINGS(test)
{
    function("test", &test);
}