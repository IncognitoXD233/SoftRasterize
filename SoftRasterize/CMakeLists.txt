cmake_minimum_required(VERSION 3.10)
project(SoftRasterizer)

include(FindPkgConfig)
pkg_check_modules(SFML REQUIRED IMPORTED_TARGET sfml-graphics sfml-window sfml-system)

include_directories("/ucrt64/include")
link_directories("/ucrt64/lib")
include_directories(include)

add_executable(SoftRasterizer
    src/main.cpp
    src/Framebuffer/framebuffer.cpp
    src/Renderer/renderer.cpp
    src/Window/window.cpp
)

set_target_properties(SoftRasterizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
)

target_link_libraries(SoftRasterizer sfml-graphics sfml-window sfml-system)