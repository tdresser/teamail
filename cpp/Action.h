
#pragma once

#include <nlohmann/json.hpp>
#include "Point.h"
#include "State.h"

enum class ActionType { Unknown, TouchStart, TouchMove };

JSON_SERIALIZE_ENUM(ActionType,
                    {
                        {ActionType::Unknown, "unknown"},
                        {ActionType::TouchStart, "touchstart"},
                        {ActionType::TouchMove, "touchmove"},
                    });

class Action {
 public:
  Action(ActionType type, Point point) : _type(type), _point(point) {}
  Action() = default;

  State reduce(State state) { return state; }
  [[nodiscard]] ActionType type() const { return _type; };
  [[nodiscard]] const Point& point() const { return _point; }
  void toJson(json& j) const;
  void fromJson(const json& j);

 private:
  ActionType _type = ActionType::Unknown;
  Point _point;
};

TO_JSON(Action, action);
FROM_JSON(Action, action);
