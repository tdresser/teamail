#include <map>
#include <string>

using string = std::string;

class Gapi {
 public:
  inline void setAuthToken(string authToken) {
    _authToken = std::move(authToken);
    fetchEmailList();
  }

  void fetchEmailList();
  void fetchGapi(string url, string postBody, string queryParameters);
  string encodeParameters(const string& url,
                          const std::map<string, string>& params);

 private:
  std::string _authToken;
};
