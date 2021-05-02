#include <cstdio>
#include <nlohmann/json.hpp>
#include <string>
#include "emscripten/bind.h"
#include "emscripten/val.h"

#include "Action.h"
#include "Point.h"
#include "State.h"

using val = emscripten::val;
using json = nlohmann::json;
using string = std::string;

string getStringCC() {
  val window = val::global("window");
  val str = window.call<val>("getString");

  return str.as<string>();
}

extern string getCardOffset() {
  json j;
  Point p(100, 120);
  p.toJson(j);
  return to_string(j);
}

extern "C" int testGetString() {
  Point point(10, 11);
  Action action(ActionType::TouchStart, point);
  json j;
  action.toJson(j);

  printf("%s\n", to_string(j).c_str());

  json actionJsonString = R"(
    {
      "type": "touchstart",
      "point": {"x": 17, "y": 19}
    }
  )"_json;
  auto recovered = actionJsonString.get<Action>();
  printf("Recovered JSON: %d, %f, %f\n", action.type(), action.point().x(),
         action.point().y());

  printf("%s\n", getStringCC().c_str());
  return 7;
}

State reduce(Action action) {
  return action.reduce(State::instance());
}

EMSCRIPTEN_BINDINGS(geometry) {
  emscripten::function<string>("getCardOffset", &getCardOffset);
  emscripten::function<int>("testGetString", &testGetString);
};
