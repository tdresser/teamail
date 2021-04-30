#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "point.h"

using json = nlohmann::json;

class State {
 public:
  State() = default;
  Point transform();
  void toJson(json& j) const { j = json{{"transform", _transform}}; }
  static State& instance() {
    if (s_instance == nullptr) {
      s_instance = std::make_unique<State>();
    }
    return *s_instance;
  }

 private:
  Point _transform;
  static std::unique_ptr<State> s_instance;
};

TO_JSON(State, state)