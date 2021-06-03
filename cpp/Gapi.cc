#include "Gapi.h"
#include <map>
#include <optional>
#include "Fetch.h"

using string = std::string;

const string GMAIL_BASE_URL = "https://gmail.googleapis.com/gmail/v1/users/me";
const string THREADS_URL = GMAIL_BASE_URL + "/threads";
const string MESSAGES_URL = GMAIL_BASE_URL + "/messages";
const string LABELS_URL = GMAIL_BASE_URL + "/labels";

const string QUERY = "in:inbox -in:chats";  // TODO(tdresser)
// const namesToExclude = Object.values(LabelName).join('" -in:"');
// const query = `in:inbox -in:chats -in:"${namesToExclude}"`;

void Gapi::fetchThreads(const string& query) {
  fetch(THREADS_URL, "GET", std::nullopt, {{"q", query}});
};

// Based on https://stackoverflow.com/a/53593869/926929.
string encodeURIComponent(const string& component) {
  const string hexDigits = "0123456789ABCDEF";
  string ret;
  for (char c : component) {
    if ((c >= 48 /*0*/ && c <= 57 /*9*/) || (c >= 97 /*a*/ && c <= 122 /*z*/) ||
        (c >= 65 /*A*/ && c <= 90 /*Z*/) || c == 45 /*-*/ || c == 95 /*_*/ ||
        c == 46 /*.*/ || c == 33 /*!*/ || c == 126 /*~*/ || c == 42 /***/ ||
        c == 92 /*\\*/ || c == 40 /*(*/ || c == 41 /*)*/) {
      ret += c;
    } else {
      ret += '%';
      ret += hexDigits[(static_cast<unsigned char>(c) & 0xF0U) >> 4U];
      ret += hexDigits[(static_cast<unsigned char>(c) & 0x0FU)];
    }
  }
  return ret;
};

void Gapi::fetchGapi(const string& url,
                     const std::optional<string>& postBody,
                     HTTPParams queryParameters) {
  HTTPParams params = {{"alt", "json"}, {"max-result", "100"}};
  params.merge(queryParameters);
  string fullUrl = encodeParameters(url, params);
  HTTPParams headers = {{"Content-Type", "application/json"},
                        {"Authorization", ""},
                        {"Accept", "*/*"},
                        {"Access-Control-Allow-Headers", "*"},
                        {"X-Requested-With", "XMLHttpRequest"},
                        {"Authorization", "Bearer " + _authToken}};

  const string method = postBody.has_value() ? "POST" : "GET";
  fetch(url, method, postBody, headers);
}
/*

let response = await fetch(fullUrl, options);
// 401 happens when auth credentials expire (and probably in other cases too).
if (response.status == = 401) {
  console.log('Retrying credentials');
  await login();
  response = await fetch(fullUrl, options);
}
return response;
}
*/

string Gapi::encodeParameters(const string& url,
                              const std::map<string, string>& params) {
  string ret = url + "?";

  for (const auto& kv : params) {
    ret += encodeURIComponent(kv.first) + "=" + encodeURIComponent(kv.second) +
           "&";
  }
  ret = ret.substr(0, ret.size() - 1);
  return ret;
}
void Gapi::setAuthToken(string authToken) {
  _authToken = std::move(authToken);
  fetchThreads(QUERY);
}
