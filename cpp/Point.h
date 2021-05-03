#pragma once

#include "JsonUtil.h"
#include "nlohmann/json_fwd.hpp"

using json = nlohmann::json;

class Point {
 public:
  Point(float x, float y) : _x(x), _y(y) {}
  Point() = default;

  void toJson(json& j) const;
  void fromJson(const json& j);

  [[nodiscard]] float x() const { return _x; }
  [[nodiscard]] float y() const { return _y; }

 private:
  float _x = 0;
  float _y = 0;
};

TO_JSON_DECLARE(Point, point);
FROM_JSON_DECLARE(Point, point);
