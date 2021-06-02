#include "../Gapi.h"

#include <gtest/gtest.h>
#include <string>

TEST(Gapi, EncodeParameters) {
  Gapi gapi;
  string encoded =
      gapi.encodeParameters("www.google.com", {{"q", "cats"}, {"foo", "b ar"}});

  // TODO(tdresser): ideally this would be order independent.
  EXPECT_EQ("www.google.com?foo=b%20ar&q=cats", encoded);
}
