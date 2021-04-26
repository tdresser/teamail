#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include <string>

using namespace emscripten;
using json = nlohmann::json;
using string = std::string;

string getStringCC() {
  val window = val::global("window");
  val str = window.call<val>("getString");

  return str.as<string>();
}

class Point {
 public:
  Point(float x, float y) : _x(x), _y(y){};

  float x() const { return _x; }
  float y() const { return _y; }

 private:
  float _x;
  float _y;
};

void to_json(json& j, const Point& p) {
  j = json{{"x", p.x()}, {"y", p.y()}};
}

extern string getCardOffset() {
  json j;
  to_json(j, Point(100, 120));
  return to_string(j);
}

extern "C" int testGetString() {
  printf("%s\n", getStringCC().c_str());
  return 7;
}

EMSCRIPTEN_BINDINGS(geometry) {
  function<string>("getCardOffset", &getCardOffset);
  function<int>("testGetString", &testGetString);
};