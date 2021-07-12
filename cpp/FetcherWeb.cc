#include "FetcherWeb.h"
#include <cstdio>
#include <cstring>
#include <optional>
#include <string>
#include "Util.h"
#include "emscripten/fetch.h"

void downloadSucceeded(emscripten_fetch_t* fetch) {
  printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes,
         fetch->url);
  // The data is now available at fetch->data[0] through
  // fetch->data[fetch->numBytes-1];
  emscripten_fetch_close(fetch);  // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t* fetch) {
  printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url,
         fetch->status);
  emscripten_fetch_close(fetch);  // Also free data on failure.
}

void FetcherWeb::fetch(const std::string& url,
                       const std::string& method,
                       const std::optional<std::string>& postBody,
                       const HTTPParams& headers) {
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, method.c_str());  // NOLINT
  attr.requestHeaders = mapToCArray(headers);

  if (postBody.has_value()) {
    attr.requestData = postBody->c_str();
    // TODO(tdresser): set attr.requestDataSize?
  }
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = downloadSucceeded;
  attr.onerror = downloadFailed;
  emscripten_fetch(&attr, url.c_str());
}
