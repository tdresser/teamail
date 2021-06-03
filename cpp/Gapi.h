#include <map>
#include <string>
#include "Fetch.h"

using string = std::string;

class Gapi {
 public:
  void setAuthToken(string authToken);
  void fetchThreads(const string& query);
  void fetchGapi(const string& url,
                 const std::optional<string>& postBody,
                 HTTPParams queryParameters);
  string encodeParameters(const string& url, const HTTPParams& params);

 private:
  std::string _authToken;
};
