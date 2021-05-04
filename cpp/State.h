#pragma once

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>

#include "JsonUtil.h"
#include "Point.h"

using json = nlohmann::json;

class State {
 public:
  State() = default;
  inline Point transform() { return _transform; };
  inline std::optional<Point> origin() { return _origin; };
  void setOrigin(Point point);
  void setTransform(Point point);
  void toJson(json& j) const;
  static State& instance();

 private:
  // Serialized.
  Point _transform;

  // Not serialized.
  std::optional<Point> _origin;
  static std::unique_ptr<State> s_instance;
};

TO_JSON_DECLARE(State, state);
