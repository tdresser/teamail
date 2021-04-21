cmake_minimum_required(VERSION 3.16)

project(Teamail)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
add_executable (Main main.cc test.cc)

set(EMS
    "SHELL:-s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall'] -s ENVIRONMENT='web' -s SAFE_HEAP=1 -s ALLOW_MEMORY_GROWTH=1"
    # -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0  EXPORT_ES6=1
)
target_compile_options(Main PRIVATE ${EMS})
target_link_options(Main PRIVATE ${EMS})
set_target_properties(Main PROPERTIES LINK_FLAGS "--bind")

# set(CMAKE_C_COMPILER "emcc")
# CMAKE_CXX_COMPILER
# set_target_properties(Engine PROPERTIES LINK_FLAGS "-o dist/engine.js -s USE_FREETYPE=1 -s DISABLE_EXCEPTION_CATCHING=0 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 --bind -s WASM=1 -O2 -s LEGACY_GL_EMULATION=0  -s GL_UNSAFE_OPTS=0 --pre-js pre-module.js --post-js post-module.js -s ASSERTIONS=1 -s GL_ASSERTIONS=1 -s INVOKE_RUN=0  -std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1 --preload-file textures --preload-file shaders --preload-file fonts")
