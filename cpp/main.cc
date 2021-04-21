#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>
#include <string>

using namespace emscripten;
using namespace std;

string getStringCC()
{
  val window = val::global("window");
  printf("About to get string\n");
  val str = window.call<val>("getString");
  printf("Got string\n");

  return str.as<string>();
}

struct PointS
{
  float x;
  float y;
};
/*
class Point : public PointS
{
public:
  Point(float x, float y)
  {
    PointS::x = x;
    PointS::y = y;
  };
};*/

EMSCRIPTEN_BINDINGS(geometry)
{
  class_<PointS>("Point")
      .property("x", &PointS::x)
      .property("y", &PointS::y);
};

EMSCRIPTEN_KEEPALIVE
extern "C" PointS getCardOffset()
{
  PointS test;
  test.x = 10;
  test.y = 11;
  return test;
}

EMSCRIPTEN_KEEPALIVE
extern "C" int main()
{
  printf("%s\n", getStringCC().c_str());
  return 7;
}