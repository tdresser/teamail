#include <cstdio>
#include <string>
#include "emscripten/bind.h"
#include "emscripten/val.h"
#include "nlohmann/json.hpp"

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

State reduce(Action action) {
  return action.reduce(State::instance());
}

string reduceWithActionString(const string& actionString) {
  printf("%s\n", actionString.c_str());
  json actionJSON = json::parse(actionString);
  Action action;
  action.fromJson(actionJSON);

  State newState = action.reduce(State::instance());
  json newStateJSON;
  newState.toJson(newStateJSON);
  return newStateJSON;
}

EMSCRIPTEN_BINDINGS(geometry) {
  emscripten::function<string>("reduce", &reduceWithActionString);
};
