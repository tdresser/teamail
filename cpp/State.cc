#include "State.h"
#include <nlohmann/json.hpp>
#include "Action.h"

using json = nlohmann::json;

std::unique_ptr<State> State::s_instance = nullptr;

void State::toJson(json& j) const {
  j = json{{"transform", _transform}};
}

void State::setOrigin(Point point) {
  _origin = point;
}

void State::clearOrigin() {
  _origin.reset();
}

void State::setTransform(Point point) {
  _transform = point;
}

State& State::instance() {
  return *s_instance;
}

void State::setInstance(std::unique_ptr<State>(state)) {
  s_instance = std::move(state);
};

void State::reduceAll(const std::vector<Action>& actions) {
  if (actions.size() > 1000) {
    printf("The action queue contains %zu actions. That's too many!\n",
           actions.size());
  }
  for (const Action& action : actions) {
    action.reduce(*this);
  }
}

TO_JSON(State, state);
