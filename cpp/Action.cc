#include "Action.h"
#include <cstdio>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void Action::toJson(json& j) const {
  j = json{{"type", _type}, {"point", _point}, {"text", _text}};
}
void Action::fromJson(const json& j) {
  j.at("type").get_to(_type);
  j.at("point").get_to(_point);
  j.at("text").get_to(_text);
}

State Action::reduce(State state) const {
  switch (_type) {
    case ActionType::TouchStart:
      state.setOrigin(_point);
      state.setTransform(Point(0, 0));
      break;
    case ActionType::TouchMove:
      state.setTransform(_point - *state.origin());
      break;
    case ActionType::TouchEnd:
      state.clearOrigin();
      state.setTransform(Point(0, 0));
      break;
    default:
      printf("Unknown action type %d\n", static_cast<int>(_type));
  }
  return state;
}

void Action::validate() {
  switch (_type) {
    case ActionType::TouchStart:
    case ActionType::TouchMove:
    case ActionType::TouchEnd:
      if (!_text.empty()) {
        printf("Invalid action.\n");
      }
      break;
    case ActionType::Auth:
      if (_point != Point()) {
        printf("Invalid action.\n");
      }
      break;
    case ActionType::Unknown:
      if (_point != Point() || !_text.empty()) {
        printf("Invalid action.\n");
      }
  }
};

TO_JSON(Action, action);
FROM_JSON(Action, action);
