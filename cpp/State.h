#pragma once

#include <memory>
#include <nlohmann/json_fwd.hpp>

#include "JsonUtil.h"
#include "Point.h"

using json = nlohmann::json;

class State {
 public:
  State() = default;
  Point transform();
  void toJson(json& j) const;
  static State& instance();

 private:
  Point _transform;
  static std::unique_ptr<State> s_instance;
};

TO_JSON_DECLARE(State, state);
