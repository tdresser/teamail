#include <string>

class ResourceManager {
 public:
  inline void setAuthToken(std::string authToken) {
    _authToken = std::move(authToken);
    fetchEmailList();
  }

  void fetchEmailList();

 private:
  std::string _authToken;
};
