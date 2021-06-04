#include <map>
#include <memory>
#include <string>
#include "Fetcher.h"

using string = std::string;

class Gapi {
 public:
  explicit Gapi(std::unique_ptr<Fetcher> fetcher)
      : _fetcher(std::move(fetcher)){};
  void setAuthToken(string authToken);
  void fetchThreads(const string& query);
  void fetchGapi(const string& url,
                 const std::optional<string>& postBody,
                 HTTPParams queryParameters);
  string encodeParameters(const string& url, const HTTPParams& params);

 private:
  std::string _authToken;
  std::unique_ptr<Fetcher> _fetcher;
};
