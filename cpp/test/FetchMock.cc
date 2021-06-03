#include <optional>
#include <string>
#include "../Fetch.h"

void fetch(const std::string& url,
           const std::string& method,
           const std::optional<std::string>& postBody,
           const HTTPParams& headers){};
