#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Point {
 public:
  Point(float x, float y) : _x(x), _y(y) {}
  Point() {}

  float x() const { return _x; }
  float y() const { return _y; }

  void to_json(json& j) const { j = json{{"x", _x}, {"y", _y}}; }

  void from_json(const json& j) {
    j.at("x").get_to(_x);
    j.at("y").get_to(_y);
  }

 private:
  float _x = 0;
  float _y = 0;
};

void to_json(json& j, const Point& p) {
  p.to_json(j);
}

void from_json(const json& j, Point& p) {
  p.from_json(j);
}