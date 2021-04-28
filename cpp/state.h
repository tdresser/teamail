#pragma once

#include <nlohmann/json.hpp>
#include "point.h"

using json = nlohmann::json;

class State {
 public:
  State(){};
  Point transform();
  void to_json(json& j) const { j = json{{"transform", _transform}}; }
  void from_json(const json& j) { j.at("transform").get_to(_transform); }

 private:
  Point _transform;
};

// TODO: maybe generate this with a macro?
void to_json(json& j, const State& state) {
  state.to_json(j);
}

void from_json(const json& j, State& state) {
  state.from_json(j);
}