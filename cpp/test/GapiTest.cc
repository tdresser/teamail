#include "../Gapi.h"

#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "MockFetcher.h"

TEST(Gapi, EncodeParameters) {
  std::unique_ptr<Fetcher> fetcher = std::make_unique<MockFetcher>();
  Gapi gapi(std::move(fetcher));
  string encoded =
      gapi.encodeParameters("www.google.com", {{"q", "cats"}, {"foo", "b ar"}});

  // TODO(tdresser): ideally this would be order independent.
  EXPECT_EQ("www.google.com?foo=b%20ar&q=cats", encoded);
}
