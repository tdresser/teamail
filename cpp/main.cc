#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <cstdio>
#include <nlohmann/json.hpp>
#include <string>

#include "action.h"
#include "point.h"
#include "state.h"

using namespace emscripten;
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

State state;

State reduce(Action action) {
  return action.reduce(state);
}

EMSCRIPTEN_BINDINGS(geometry) {
  function<string>("getCardOffset", &getCardOffset);
  function<int>("testGetString", &testGetString);
};