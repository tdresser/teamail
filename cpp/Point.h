#pragma once

#include "JsonUtil.h"
#include "nlohmann/json_fwd.hpp"

using json = nlohmann::json;

class Point {
 public:
  Point(float x, float y) : _x(x), _y(y) {}
  Point() = default;

  inline Point operator-(const Point& p) const {
    return Point(_x - p.x(), _y - p.y());
  }

  inline Point operator+(const Point& p) const {
    return Point(_x + p.x(), _y + p.y());
  }

  inline bool operator==(const Point& p) const {
    return _x == p.x() && _y == p.y();
  }

  inline bool operator!=(const Point& p) const { return !(*this == p); }

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
