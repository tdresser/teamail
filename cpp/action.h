
#pragma once

#include <nlohmann/json.hpp>
#include "emscripten_util.h"
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
  Action() = default;
  ;
  // TODO(tdresser) - make this virtual, and use polymorphism?
  State reduce(State state) { return state; }
  [[nodiscard]] ActionType type() const { return _type; };
  [[nodiscard]] const Point& point() const { return _point; }
  void toJson(json& j) const { j = json{{"type", _type}, {"point", _point}}; }
  void fromJson(const json& j) {
    j.at("type").get_to(_type);
    j.at("point").get_to(_point);
  }

 private:
  ActionType _type = ActionType::Unknown;
  Point _point;
};

TO_JSON(Action, action);
FROM_JSON(Action, action);
