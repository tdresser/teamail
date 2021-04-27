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
  void init(float x, float y) {
    _x = x;
    _y = y;
  }

  float x() const { return _x; }
  float y() const { return _y; }

 private:
  float _x;
  float _y;
};

void to_json(json& j, const Point& p) {
  j = json{{"x", p.x()}, {"y", p.y()}};
}

void from_json(const json& j, Point& p) {
  p.init(j.at("x").get<float>(), j.at("y").get<float>());
}

enum class ActionType { TouchStart, TouchMove };

NLOHMANN_JSON_SERIALIZE_ENUM(ActionType,
                             {
                                 {ActionType::TouchStart, "touchstart"},
                                 {ActionType::TouchMove, "touchmove"},
                             });

class Action {
 public:
  void init(ActionType type, Point point) {
    _type = type;
    _point = point;
  }
  ActionType type() const { return _type; };
  const Point& point() const { return _point; }

 private:
  ActionType _type;
  Point _point;
};

void to_json(json& j, const Action& action) {
  j = json{{"type", action.type()}, {"point", action.point()}};
}

void from_json(const json& j, Action& action) {
  action.init(j.at("type").get<ActionType>(), j.at("point").get<Point>());
}

extern string getCardOffset() {
  json j;
  Point p;
  p.init(100, 120);
  to_json(j, p);
  return to_string(j);
}

extern "C" int testGetString() {
  Point point;
  point.init(10, 11);
  Action action;
  action.init(ActionType::TouchStart, point);
  json j;
  to_json(j, action);
  printf("%s\n", to_string(j).c_str());

  json action_json_string = R"(
    {
      "type": 1,
      "point": {"x": 17, "y": 19}
    }
  )"_json;
  Action recovered = action_json_string.get<Action>();
  printf("Recovered JSON: %d, %f, %f\n", action.type(), action.point().x(),
         action.point().y());

  printf("%s\n", getStringCC().c_str());
  return 7;
}

EMSCRIPTEN_BINDINGS(geometry) {
  function<string>("getCardOffset", &getCardOffset);
  function<int>("testGetString", &testGetString);
};