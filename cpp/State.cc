#include "State.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void State::toJson(json& j) const {
  j = json{{"transform", _transform}};
}

State& State::instance() {
  if (s_instance == nullptr) {
    s_instance = std::make_unique<State>();
  }
  return *s_instance;
}

TO_JSON(State, state);
