#include <map>
#include <string>

// Converts a map<string, string> to a [key, value, key, value] array.
// Allocates memory.
const char* const* mapToCArray(
    const std::map<std::string, std::string>& headers);
