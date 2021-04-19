#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>
#include <string>

using namespace emscripten;
using namespace std;

string getStringCC() {
  val window = val::global("window");
  val str = window.call<val>("getString");

  return str.as<string>();
}

struct PointS {
    float x;
    float y;
};

class Point : public PointS {
    public:
      Point(float x, float y) {
          PointS::x = x;
          PointS::y = y;
      };
};

EMSCRIPTEN_BINDINGS(geometry) {
  class_<PointS>("Point")
    .property("x", &PointS::x)
    .property("y", &PointS::y);
};

EMSCRIPTEN_KEEPALIVE 
extern "C" PointS getCardOffset() {
    return static_cast<PointS>(Point(200, 300));
}

EMSCRIPTEN_KEEPALIVE 
extern "C" int main() {
    printf("%s\n", getStringCC().c_str());
    return 7;
}