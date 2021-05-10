#pragma once

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>

#include "JsonUtil.h"
#include "Point.h"

class Action;

using json = nlohmann::json;

class State {
 public:
  State() = default;
  inline Point transform() { return _transform; };
  inline std::optional<Point> origin() { return _origin; };
  void setOrigin(Point point);
  void clearOrigin();
  void setTransform(Point point);
  void toJson(json& j) const;
  State reduceAll(const std::vector<Action>& actions);
  static State& instance();
  static void setInstance(State state);

 private:
  // Serialized.
  Point _transform;

  // Not serialized.
  std::optional<Point> _origin;
  static std::unique_ptr<State> s_instance;
};

TO_JSON_DECLARE(State, state);
