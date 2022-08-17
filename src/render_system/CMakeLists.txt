
add_subdirectory(shaders)

add_library(render-system-lib
    render_defaults.cpp
    camera.cpp
    renderer.cpp
    #gui_renderer.cpp
    texture.cpp
    frame_buffer.cpp
    #post_processor.cpp
    default_primitives_renderer.cpp
)

target_link_libraries(render-system-lib shaders-lib)
