#include <memory>
#include <nlohmann/json.hpp>
#include "../Action.h"
#include "../State.h"
#include "MockFetcher.h"

#include <gtest/gtest.h>

using testing::_;

TEST(Action, Serialize) {
  Action action(ActionType::TouchStart, Point(1, 10));
  json j;
  action.toJson(j);
  EXPECT_EQ("touchstart", j.at("type").get<std::string>());
  EXPECT_EQ(1, j.at("point").at("x").get<float>());
  EXPECT_EQ(10, j.at("point").at("y").get<float>());
}

TEST(Action, DeserializePointerAction) {
  json j = R"(
    {
      "type": "touchstart",
      "point": {
        "x": 1,
        "y": 2
      }
    }
  )"_json;

  Action action;
  action.fromJson(j);

  EXPECT_EQ(Action(ActionType::TouchStart, Point(1, 2)), action);
}

TEST(Action, ReducePointer) {
  State state(std::make_unique<MockFetcher>());
  EXPECT_FALSE(state.origin().has_value());
  EXPECT_EQ(Point(0, 0), state.transform());

  Action(ActionType::TouchStart, Point(1, 10)).reduce(state);
  EXPECT_EQ(Point(1, 10), *state.origin());
  EXPECT_EQ(Point(0, 0), state.transform());

  Action(ActionType::TouchMove, Point(11, 20)).reduce(state);
  EXPECT_EQ(Point(1, 10), *state.origin());
  EXPECT_EQ(Point(10, 10), state.transform());

  Action(ActionType::TouchMove, Point(11, 20)).reduce(state);
  EXPECT_EQ(Point(1, 10), *state.origin());
  EXPECT_EQ(Point(10, 10), state.transform());
}

TEST(Action, ReduceAuth) {
  std::unique_ptr<MockFetcher> fetcher = std::make_unique<MockFetcher>();
  EXPECT_CALL(*fetcher, fetch(_, _, _, _)).Times(1);
  State state(std::move(fetcher));

  Action(ActionType::Auth, "fake-token").reduce(state);
  // TODO(tdresser)
}
