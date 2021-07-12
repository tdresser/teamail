#include "../Gapi.h"

#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "MockFetcher.h"

const std::string THREAD_RESPONSE = R"e(
{
  "threads": [
    {
      "id": "179eb713338856e1",
      "snippet": "Snippet A",
      "historyId": "14708495"
    },
    {
      "id": "179eac3f786456c7",
      "snippet": "Snippet B",
      "historyId": "14707371"
    },
    {
      "id": "179e8d668fd2791a",
      "snippet": "Snippet C",
      "historyId": "14704951"
    }
  ],
  "resultSizeEstimate": 3
}
)e";

TEST(Gapi, EncodeParameters) {
  std::unique_ptr<Fetcher> fetcher = std::make_unique<MockFetcher>();
  Gapi gapi(std::move(fetcher));
  string encoded =
      gapi.encodeParameters("www.google.com", {{"q", "cats"}, {"foo", "b ar"}});

  // TODO(tdresser): ideally this would be order independent.
  EXPECT_EQ("www.google.com?foo=b%20ar&q=cats", encoded);
}

TEST(Gapi, FetchThreads) {
  std::unique_ptr<Fetcher> fetcher = std::make_unique<MockFetcher>();
  Gapi gapi(std::move(fetcher));
  gapi.fetchThreads("test: foo");
}
