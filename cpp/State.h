#pragma once

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <utility>

#include "Gapi.h"
#include "JsonUtil.h"
#include "Point.h"

class Action;

using json = nlohmann::json;

class State {
 public:
  State() = default;
  inline Point transform() { return _transform; };
  void setTransform(Point point);

  inline std::optional<Point> origin() { return _origin; };
  void setOrigin(Point point);
  void clearOrigin();

  inline void setAuthToken(std::string authToken) {
    _gapi.setAuthToken(std::move(authToken));
  }

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
  Gapi _gapi;
};

TO_JSON_DECLARE(State, state);
