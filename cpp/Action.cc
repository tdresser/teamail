#include "Action.h"

void Action::toJson(json& j) const {
  j = json{{"type", _type}, {"point", _point}};
}
void Action::fromJson(const json& j) {
  j.at("type").get_to(_type);
  j.at("point").get_to(_point);
}
