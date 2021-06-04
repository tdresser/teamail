#pragma once

#include "Fetcher.h"

class FetcherWeb : public Fetcher {
 public:
  void fetch(const std::string& url,
             const std::string& method,
             const std::optional<std::string>& postBody,
             const HTTPParams& headers) override;
};
