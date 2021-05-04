#include <nlohmann/json.hpp>
#include "../Action.h"
#include "../State.h"

#include <gtest/gtest.h>

TEST(Action, Serialize) {
  Action action(ActionType::TouchStart, Point(1, 10));
  json j;
  action.toJson(j);
  EXPECT_EQ("touchstart", j.at("type").get<std::string>());
  EXPECT_EQ(1, j.at("point").at("x").get<float>());
  EXPECT_EQ(10, j.at("point").at("y").get<float>());
}

TEST(Action, Reduce) {
  State state;
  EXPECT_FALSE(state.origin().has_value());
  EXPECT_EQ(Point(0, 0), state.transform());

  state = Action(ActionType::TouchStart, Point(1, 10)).reduce(state);
  EXPECT_EQ(Point(1, 10), *state.origin());
  EXPECT_EQ(Point(0, 0), state.transform());

  state = Action(ActionType::TouchMove, Point(11, 20)).reduce(state);
  EXPECT_EQ(Point(1, 10), *state.origin());
  EXPECT_EQ(Point(10, 10), state.transform());
}
