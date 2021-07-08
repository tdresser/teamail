#include "../Util.h"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

std::vector<std::string> cArrayToVector(const char* const* ar) {
  std::vector<std::string> ret;

  int i = 0;
  while (ar[i] != nullptr) {
    ret.push_back(std::string(ar[i]));  // NOLINT
    ++i;
  }
  return ret;
}

TEST(Gapi, MapToCArray) {
  const char* const* cArray =
      mapToCArray({{"key1", "value1"}, {"key2", "value2"}});
  std::vector<std::string> result = cArrayToVector(cArray);
  EXPECT_THAT(result, testing::UnorderedElementsAre("key1", "value1", "key2",
                                                    "value2"));
}
