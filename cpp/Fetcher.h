#pragma once

#include <map>
#include <string>

using HTTPParams = std::map<std::string, std::string>;

class Fetcher {
 public:
  virtual void fetch(const std::string& url,
                     const std::string& method,
                     const std::optional<std::string>& postBody,
                     const HTTPParams& headers) = 0;
  virtual ~Fetcher() = default;
};
