#include "Action.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void Action::toJson(json& j) const {
  j = json{{"type", _type}, {"point", _point}};
}
void Action::fromJson(const json& j) {
  j.at("type").get_to(_type);
  j.at("point").get_to(_point);
}

TO_JSON(Action, action);
FROM_JSON(Action, action);
