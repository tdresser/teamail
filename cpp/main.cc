#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>
#include <string>

using namespace emscripten;
using string = std::string;

string getStringCC()
{
  val window = val::global("window");
  val str = window.call<val>("getString");

  return str.as<string>();
}

struct PointS
{
  float x;
  float y;
};

class Point : public PointS
{
public:
  Point(float x, float y)
  {
    PointS::x = x;
    PointS::y = y;
  };
};

extern "C" PointS getCardOffset()
{
  return Point(100, 120);
}

extern "C" int testGetString()
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
  function<int>("testGetString", &testGetString);
};