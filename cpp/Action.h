
#pragma once

#include <string>
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
  Action(ActionType type, Point point) : _type(type), _point(point){};
  Action(ActionType type, std::string text)
      : _type(type), _text(std::move(text)) {}

  Action() = default;

  void reduce(State& state) const;
  [[nodiscard]] ActionType type() const { return _type; };
  [[nodiscard]] const Point& point() const { return _point; }
  [[nodiscard]] std::string text() const { return _text; }
  void toJson(json& j) const;
  void fromJson(const json& j);
  inline bool operator==(const Action& o) const {
    return _type == o.type() && _point == o.point() && _text == o.text();
  }

 private:
  ActionType _type = ActionType::Unknown;
  Point _point;
  std::string _text;
};

TO_JSON_DECLARE(Action, action);
FROM_JSON_DECLARE(Action, action);
