 
add_subdirectory(glsl)

add_library(shaders-lib
    uniform_buffer.cpp
    general_vs_ubo.cpp
    program.cpp
    object_2d.cpp
    line_2d.cpp
)
