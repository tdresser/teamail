#include "Gapi.h"
#include <map>
#include "Fetch.h"

using string = std::string;

void Gapi::fetchEmailList() {
  printf("%s\n", _authToken.c_str());
  fetch("http://www.google.com");
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

void fetchGapi(const string& url,
               const string& postBody,
               const string& queryParameters) {}

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

/*
  const fullUrl = encodeParameters(url, {
    alt : 'json',
    'max-results' : 100,
    ... queryParameters,
  });

  const headers = new Headers({
    'Content-Type' : 'application/json',
    Authorization : '',
    Accept : '*//*
        * ', ' Access
    - Control - Allow - Headers ' : ' * ', ' X - Requested
    - With ' : ' XMLHttpRequest',
});
headers.set('Authorization', 'Bearer ' + accessToken);

const options : RequestInit = {headers};
if (postBody) {
  options.method = 'POST';
  options.body = JSON.stringify(postBody);
} else {
  options.method = 'GET';
}
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
