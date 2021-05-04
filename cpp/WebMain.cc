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

State reduceWithActionString(string actionString) {
  json actionJSON(actionString);
  Action action;
  action.fromJson(actionJSON);
  // TODO(tdresser) - copy State objects less.
  return action.reduce(State::instance());
}

EMSCRIPTEN_BINDINGS(geometry) {
  emscripten::function<State>("reduce", &reduceWithActionString);
};
