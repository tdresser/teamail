#pragma once

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <utility>

#include "Fetcher.h"
#include "Gapi.h"
#include "JsonUtil.h"
#include "Point.h"

class Action;

using json = nlohmann::json;

class State {
 public:
  explicit State(std::unique_ptr<Fetcher> fetcher)
      : _gapi(std::move(fetcher)) {}
  inline Point transform() { return _transform; };
  void setTransform(Point point);

  inline std::optional<Point> origin() { return _origin; };
  void setOrigin(Point point);
  void clearOrigin();

  inline void setAuthToken(std::string authToken) {
    _gapi.setAuthToken(std::move(authToken));
  }

  void toJson(json& j) const;

  void reduceAll(const std::vector<Action>& actions);
  static State& instance();
  static void setInstance(std::unique_ptr<State> state);

 private:
  // Serialized.
  Point _transform;

  // Not serialized.
  std::optional<Point> _origin;
  static std::unique_ptr<State> s_instance;
  Gapi _gapi;
};

TO_JSON_DECLARE(State, state);
