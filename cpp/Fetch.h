#include <map>
#include <string>

using HTTPParams = std::map<std::string, std::string>;

void fetch(const std::string& url,
           const std::string& method,
           const std::optional<std::string>& postBody,
           const HTTPParams& headers);
