# TODO - strip trailing spaces.

cmake_minimum_required(VERSION 3.16)

project(Teamail)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

# Get the absolute path of $ROOT/deps.
get_filename_component(deps_dir "../deps"
                       REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")

# Fetch Dependencies
set(FETCHCONTENT_BASE_DIR ${deps_dir})

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Lib

add_library(Lib STATIC
  Action.cc
  Point.cc
  State.cc)

target_link_libraries(Lib PUBLIC nlohmann_json::nlohmann_json)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(Lib PROPERTIES
CXX_STANDARD 20)

# WEB

add_executable(Web)

target_sources(Web PUBLIC
    WebMain.cc
    WebTest.cc)

target_compile_options(Web PRIVATE ${EMS})
target_link_options(Web PRIVATE ${EMS})

set_target_properties(Web PROPERTIES
  CXX_STANDARD 20
  COMPILE_FLAGS "-m32"
  LINK_FLAGS "-m32 --bind")

target_link_libraries(Web PUBLIC Lib)

target_include_directories(Web
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../deps/emsdk/upstream/emscripten/system/include/>)

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
