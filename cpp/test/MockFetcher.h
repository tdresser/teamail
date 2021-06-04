#include <gmock/gmock.h>
#include "../Fetcher.h"

class MockFetcher : public Fetcher {
 public:
  MOCK_METHOD(void,  // NOLINT
              fetch,
              (const std::string& url,
               const std::string& method,
               const std::optional<std::string>& postBody,
               const HTTPParams& headers),
              (override));

  ~MockFetcher() override = default;
};
