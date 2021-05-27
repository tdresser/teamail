#include "Action.h"
#include <cstdio>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void Action::toJson(json& j) const {
  j = json{{"type", _type}, {"point", _point}, {"text", _text}};
}
void Action::fromJson(const json& j) {
  j.at("type").get_to(_type);

  switch (_type) {
    case ActionType::TouchStart:
    case ActionType::TouchMove:
    case ActionType::TouchEnd:
      j.at("point").get_to(_point);
      break;
    case ActionType::Auth:
      j.at("text").get_to(_text);
      break;
    case ActionType::Unknown:
      printf("Invalid action.\n");
  }
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
    case ActionType::Auth:
      printf("Authing");
      printf("Token is: %s\n", _text.c_str());
      state.setAuthToken(_text);
      break;
    default:
      printf("Unknown action type %d\n", static_cast<int>(_type));
  }
  return state;
}

TO_JSON(Action, action);
FROM_JSON(Action, action);
