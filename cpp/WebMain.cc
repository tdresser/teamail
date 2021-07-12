#include <cstdio>
#include <memory>
#include <string>
#include "emscripten/bind.h"
#include "emscripten/val.h"
#include "nlohmann/json.hpp"

#include "Action.h"
#include "FetcherWeb.h"
#include "Point.h"
#include "State.h"

using val = emscripten::val;
using json = nlohmann::json;
using string = std::string;

int main() {
  std::unique_ptr<State> state =
      std::make_unique<State>(std::make_unique<FetcherWeb>());
  State::setInstance(std::move(state));
}

string getStringCC() {
  val window = val::global("window");
  val str = window.call<val>("getString");

  return str.as<string>();
}

void reduce(const std::vector<Action>& actions) {
  printf("Reduce A\n");
  State& state = State::instance();
  for (const Action& action : actions) {
    action.reduce(state);
  }
  printf("Reduce B\n");
}

string reduceWithActionsString(const string& actionsString) {
  json actionsJSON = json::parse(actionsString);
  std::vector<Action> actions;
  printf("Actions length: %zu\n", actions.size());
  actionsJSON.get_to(actions);

  State::instance().reduceAll(actions);

  json newStateJSON;
  State::instance().toJson(newStateJSON);

  return newStateJSON.dump();
}

EMSCRIPTEN_BINDINGS(geometry) {
  emscripten::function("reduce", &reduceWithActionsString);
};
