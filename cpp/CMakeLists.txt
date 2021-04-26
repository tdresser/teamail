cmake_minimum_required(VERSION 3.16)

project(Teamail)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
add_executable (Main 
    main.cc 
    test.cc
)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(Main PRIVATE nlohmann_json::nlohmann_json)

#find_package(nlohmann_json 3.2.0 REQUIRED)

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
    # -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']
)
target_compile_options(Main PRIVATE ${EMS})
target_link_options(Main PRIVATE ${EMS})
set_target_properties(Main PROPERTIES LINK_FLAGS "--bind")

# set(CMAKE_C_COMPILER "emcc")
# CMAKE_CXX_COMPILER
# set_target_properties(Engine PROPERTIES LINK_FLAGS "-o dist/engine.js -s USE_FREETYPE=1 -s DISABLE_EXCEPTION_CATCHING=0 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 --bind -s WASM=1 -O2 -s LEGACY_GL_EMULATION=0  -s GL_UNSAFE_OPTS=0 --pre-js pre-module.js --post-js post-module.js -s ASSERTIONS=1 -s GL_ASSERTIONS=1 -s INVOKE_RUN=0  -std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1 --preload-file textures --preload-file shaders --preload-file fonts")
