#include "Point.h"
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void Point::toJson(json& j) const {
  j = json{{"x", _x}, {"y", _y}};
}

void Point::fromJson(const json& j) {
  j.at("x").get_to(_x);
  j.at("y").get_to(_y);
}

TO_JSON(Point, point);
FROM_JSON(Point, point);
