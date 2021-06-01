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

State reduce(const std::vector<Action>& actions) {
  State state = State::instance();
  for (const Action& action : actions) {
    state = action.reduce(state);
  }
  State::setInstance(state);
  return state;
}

string reduceWithActionsString(const string& actionsString) {
  json actionsJSON = json::parse(actionsString);
  std::vector<Action> actions;
  printf("Actions length: %zu\n", actions.size());
  actionsJSON.get_to(actions);

  State newState = State::instance().reduceAll(actions);

  json newStateJSON;
  newState.toJson(newStateJSON);

  return newStateJSON.dump();
}

EMSCRIPTEN_BINDINGS(geometry) {
  emscripten::function("reduce", &reduceWithActionsString);
};
