
#pragma once

#include <nlohmann/json.hpp>
#include "point.h"
#include "state.h"

enum class ActionType { Unknown, TouchStart, TouchMove };

NLOHMANN_JSON_SERIALIZE_ENUM(ActionType,
                             {
                                 {ActionType::Unknown, "unknown"},
                                 {ActionType::TouchStart, "touchstart"},
                                 {ActionType::TouchMove, "touchmove"},
                             });

class Action {
 public:
  Action(ActionType type, Point point) : _type(type), _point(point) {}
  Action(){};
  // TODO - make this virtual, and use polymorphism?
  State reduce(State state) { return state; }
  ActionType type() const { return _type; };
  const Point& point() const { return _point; }
  void to_json(json& j) const { j = json{{"type", _type}, {"point", _point}}; }
  void from_json(const json& j) {
    j.at("type").get_to(_type);
    j.at("point").get_to(_point);
  }

 private:
  ActionType _type;
  Point _point;
};

// TODO: maybe generate this with a macro?
void to_json(json& j, const Action& action) {
  action.to_json(j);
}

void from_json(const json& j, Action& action) {
  action.from_json(j);
}