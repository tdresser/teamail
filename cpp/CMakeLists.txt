cmake_minimum_required(VERSION 3.16)

project(Teamail)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Get the absolute path of $ROOT/deps.
get_filename_component(deps_dir "../deps"
                       REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")

# Fetch Dependencies
set(FETCHCONTENT_BASE_DIR ${deps_dir})

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

# Lib

add_library(Lib STATIC
  Action.cc
  Point.cc
  State.cc
  Gapi.cc
  Util.cc
)

target_link_libraries(Lib PUBLIC nlohmann_json::nlohmann_json)

# Emscripten Settings
if(BUILD STREQUAL "Web")
  # -s SAFE_HEAP is another option.
  set(EMS
    "SHELL:
    -s ENVIRONMENT='web'
    -s FETCH=1
    -s ALLOW_MEMORY_GROWTH
    -g3
    -fexceptions" # exceptions are super slow and costly, TODO, disable them.
    # -s TOTAL_MEMORY=278331392
    # -fsanitize=undefined
    # -fsanitize=address
    # -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0  EXPORT_ES6=1
  )

  target_compile_options(Lib PUBLIC
    ${EMS}
    "-m32")
  target_link_options(Lib PUBLIC ${EMS}
    "-m32"
    "--bind")
endif()

# Test

# https://google.github.io/googletest/quickstart-cmake.html

add_executable(Test
  test/ActionTest.cc
  test/GapiTest.cc
  test/FetchMock.cc
  test/UtilTest.cc)

target_link_libraries(Test
  PUBLIC
    Lib
    gtest_main
    gmock)

include(GoogleTest)
gtest_discover_tests(Test)

# Web

add_executable(Web)

target_sources(Web PUBLIC
    WebMain.cc
    WebTest.cc
    EmscriptenUtil.cc
    FetchWeb.cc)

target_link_libraries(Web PUBLIC Lib)

target_include_directories(Web
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../deps/emsdk/upstream/emscripten/system/include/>)

# Global properties.
set_target_properties(Lib Web Test PROPERTIES
  CXX_STANDARD 20)
