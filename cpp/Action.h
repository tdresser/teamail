
#pragma once

#include "Point.h"
#include "State.h"

#include "nlohmann/json.hpp"

enum class ActionType { Unknown, TouchStart, TouchMove, TouchEnd };

JSON_SERIALIZE_ENUM(ActionType,
                    {
                        {ActionType::Unknown, "unknown"},
                        {ActionType::TouchStart, "touchstart"},
                        {ActionType::TouchMove, "touchmove"},
                        {ActionType::TouchEnd, "touchend"},

                    });

class Action {
 public:
  Action(ActionType type, Point point) : _type(type), _point(point) {}
  Action() = default;

  [[nodiscard]] State reduce(State state) const;
  [[nodiscard]] ActionType type() const { return _type; };
  [[nodiscard]] const Point& point() const { return _point; }
  void toJson(json& j) const;
  void fromJson(const json& j);

 private:
  ActionType _type = ActionType::Unknown;
  Point _point;
};

TO_JSON_DECLARE(Action, action);
FROM_JSON_DECLARE(Action, action);
