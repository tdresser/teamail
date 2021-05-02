cmake_minimum_required(VERSION 3.16)

project(Teamail)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

add_library(Lib
  Action.cc)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(Lib PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Lib  
  PUBLIC $<INSTALL_INTERFACE:json-src/include>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(Lib PROPERTIES
CXX_STANDARD 20)

# WEB

add_executable (Web)

target_sources(Web PUBLIC
    WebMain.cc 
    WebTest.cc)

add_dependencies(Web Lib)

target_compile_options(Web PRIVATE ${EMS})
target_link_options(Web PRIVATE ${EMS})

set_target_properties(Web PROPERTIES 
  CXX_STANDARD 20
  COMPILE_FLAGS "-m32" 
  LINK_FLAGS "-m32 --bind")

target_include_directories(Web SYSTEM  
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../deps/emsdk/upstream/emscripten/system/include/>
  PRIVATE $<INSTALL_INTERFACE:json-src/include>
  PRIVATE foo/bar)

# -s SAFE_HEAP is another option.
set(EMS
    "SHELL: 
    -s ENVIRONMENT='web' 
    -g3
    -s ALLOW_MEMORY_GROWTH
    -fexceptions" # exceptions are super slow and costly, TODO, disable them.
    # -s TOTAL_MEMORY=278331392
    # -fsanitize=undefined
    # -fsanitize=address 
    # -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0  EXPORT_ES6=1 
)
