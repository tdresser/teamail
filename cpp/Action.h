
#pragma once

#include <utility>

#include "Point.h"
#include "State.h"

#include "nlohmann/json.hpp"

enum class ActionType { Unknown, TouchStart, TouchMove, TouchEnd, Auth };

JSON_SERIALIZE_ENUM(ActionType,
                    {
                        {ActionType::Unknown, "unknown"},
                        {ActionType::TouchStart, "touchstart"},
                        {ActionType::TouchMove, "touchmove"},
                        {ActionType::TouchEnd, "touchend"},
                        {ActionType::Auth, "auth"},

                    });

class Action {
 public:
  Action(ActionType type, Point point) : _type(type), _point(point) {
    validate();
  };
  Action(ActionType type, std::string text)
      : _type(type), _text(std::move(text)) {
    validate();
  }

  Action() = default;

  [[nodiscard]] State reduce(State state) const;
  [[nodiscard]] ActionType type() const { return _type; };
  [[nodiscard]] const Point& point() const { return _point; }
  void validate();
  void toJson(json& j) const;
  void fromJson(const json& j);

 private:
  ActionType _type = ActionType::Unknown;
  Point _point;
  std::string _text;
};

TO_JSON_DECLARE(Action, action);
FROM_JSON_DECLARE(Action, action);
