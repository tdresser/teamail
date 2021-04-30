#pragma once

#include <nlohmann/json.hpp>
#include "emscripten_util.h"
using json = nlohmann::json;

class Point {
 public:
  Point(float x, float y) : _x(x), _y(y) {}
  Point() = default;

  [[nodiscard]] float x() const { return _x; }
  [[nodiscard]] float y() const { return _y; }

  void toJson(json& j) const { j = json{{"x", _x}, {"y", _y}}; }

  void fromJson(const json& j) {
    j.at("x").get_to(_x);
    j.at("y").get_to(_y);
  }

 private:
  float _x = 0;
  float _y = 0;
};

TO_JSON(Point, point);
FROM_JSON(Point, point);