cmake_minimum_required(VERSION 3.10)
project(SoftRasterizer)

include_directories(include)

add_executable(SoftRasterizer
    src/main.cpp
    src/Framebuffer/framebuffer.cpp
    src/Math/mat4.cpp
    src/Math/vec2.cpp
    src/Math/vec3.cpp
    src/Rasterize/Rasterize.cpp
    src/Renderer/renderer.cpp
    src/Window/window.cpp
)

set_target_properties(SoftRasterizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
)

target_link_libraries(SoftRasterizer sfml-graphics sfml-window)