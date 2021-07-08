#include <cstring>
#include <map>
#include <string>

// Converts a map<string, string> to a null terminated [key, value, key, value,
// nullptr] array. Allocates memory.
const char* const* mapToCArray(
    const std::map<std::string, std::string>& headers) {
  const char** formattedHeaders = static_cast<const char**>(
      malloc(sizeof(char*) *  // NOLINT - need to malloc for emscripten fetch.
                 headers.size() * 2 +
             1));
  int i = 0;
  for (const auto& kv : headers) {
    formattedHeaders[i++] = kv.first.c_str();   // NOLINT
    formattedHeaders[i++] = kv.second.c_str();  // NOLINT
  }

  formattedHeaders[i] = nullptr;
  return formattedHeaders;
}
