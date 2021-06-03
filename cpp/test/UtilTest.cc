#include "../Util.h"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

std::vector<std::string> CArrayToVector(const char* const* ar, size_t size) {
  std::vector<std::string> ret(size);

  for (int i = 0; i < size; ++i) {
    ret[i] = std::string(ar[i]);  // NOLINT
  }
  return ret;
}

TEST(Gapi, MapToCArray) {
  const char* const* cArray =
      mapToCArray({{"key1", "value1"}, {"key2", "value2"}});
  std::vector<std::string> result = CArrayToVector(cArray, 4);
  EXPECT_THAT(result, testing::UnorderedElementsAre("key1", "value1", "key2",
                                                    "value2"));
}
