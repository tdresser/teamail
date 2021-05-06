#include "Action.h"
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void Action::toJson(json& j) const {
  j = json{{"type", _type}, {"point", _point}};
}
void Action::fromJson(const json& j) {
  printf("A\n");
  j.at("type").get_to(_type);
  j.at("point").get_to(_point);
  printf("B\n");
}

State Action::reduce(State state) {
  switch (_type) {
    case ActionType::TouchStart:
      state.setOrigin(_point);
      state.setTransform(Point(0, 0));
      break;
    case ActionType::TouchMove:
      state.setTransform(state.transform() + (_point - *state.origin()));
      break;
    default:
      std::cerr << "Unknown action type." << std::endl;
  }
  return state;
}

TO_JSON(Action, action);
FROM_JSON(Action, action);
