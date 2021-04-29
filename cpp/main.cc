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
  Point(float x, float y) : _x(x), _y(y) {}
  Point() {}

  float x() const { return _x; }
  float y() const { return _y; }

  void to_json(json& j) const { j = json{{"x", _x}, {"y", _y}}; }

  void from_json(const json& j) {
    j.at("x").get_to(_x);
    j.at("y").get_to(_y);
  }

 private:
  float _x = 0;
  float _y = 0;
};

void to_json(json& j, const Point& p) {
  p.to_json(j);
}

void from_json(const json& j, Point& p) {
  p.from_json(j);
}

enum class ActionType { Unknown, TouchStart, TouchMove };

NLOHMANN_JSON_SERIALIZE_ENUM(ActionType,
                             {
                                 {ActionType::Unknown, "unknown"},
                                 {ActionType::TouchStart, "touchstart"},
                                 {ActionType::TouchMove, "touchmove"},
                             });

class Action {
 public:
  Action(ActionType type, Point point) : _type(type), _point(point) {}
  Action(){};
  ActionType type() const { return _type; };
  const Point& point() const { return _point; }
  void to_json(json& j) const { j = json{{"type", _type}, {"point", _point}}; }
  void from_json(const json& j) {
    j.at("type").get_to(_type);
    j.at("point").get_to(_point);
  }

 private:
  ActionType _type;
  Point _point;
};

// TODO: maybe generate this with a macro?
void to_json(json& j, const Action& action) {
  action.to_json(j);
}

void from_json(const json& j, Action& action) {
  action.from_json(j);
}

extern string getCardOffset() {
  json j;
  Point p(100, 120);
  to_json(j, p);
  return to_string(j);
}

extern "C" int testGetString() {
  Point point(10, 11);
  Action action(ActionType::TouchStart, point);
  json j;
  to_json(j, action);
  printf("%s\n", to_string(j).c_str());

  json action_json_string = R"(
    {
      "type": "touchstart",
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