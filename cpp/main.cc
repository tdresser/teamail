#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>
#include <string>

using namespace emscripten;
using string = std::string;

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

extern "C" PointS getCardOffset()
{
  PointS test;
  test.x = 100;
  test.y = 110;
  return test;
}

extern "C" int main()
{
  printf("%s\n", getStringCC().c_str());
  return 7;
}

EMSCRIPTEN_BINDINGS(geometry)
{
  value_object<PointS>("Point")
      .field("x", &PointS::x)
      .field("y", &PointS::y);

  function<PointS>("getCardOffset", &getCardOffset);
};