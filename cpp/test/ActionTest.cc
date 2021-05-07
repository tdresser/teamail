#include <nlohmann/json.hpp>
#include "../Action.h"

#include <gtest/gtest.h>

TEST(Action, Serialize) {
  Action action(ActionType::TouchStart, Point(1, 10));
  json j;
  action.toJson(j);
  EXPECT_EQ("touchstart", j.at("type").get<std::string>());
  EXPECT_EQ(1, j.at("point").at("x").get<float>());
  EXPECT_EQ(10, j.at("point").at("y").get<float>());
}
