#include <emscripten.h>
#include <emscripten/val.h>
#include <stdio.h>
#include <string>

using namespace emscripten;
using namespace std;

string getStringCC() {
  printf("A\n");
  val window = val::global("window");
  printf("B\n");

  val str = window.call<val>("getString");
  printf("C\n");

  //val navigator = val::global("navigator");
  //val userAgent = navigator["userAgent"];

  return str.as<string>();
}

/*EM_JS(char*, getStringCC, (), {
  let jsString =  getString();
  let lengthBytes = lengthBytesUTF8(jsString)+1;
  let stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
  return stringOnWasmHeap;
});*/

EMSCRIPTEN_KEEPALIVE 
extern "C" int main() {
    printf("%s\n", getStringCC().c_str());
    return 7;
}