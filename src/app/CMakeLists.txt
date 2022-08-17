add_library(
    app-lib
    app.cpp
    display.cpp
    input.cpp
    loaders.cpp
)
target_link_libraries(
    app-lib
    serializer-lib
    physics-lib
    render-system-lib
    ${OPENGL_LIBRARIES}
    ${GLAD_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${IMGUI_LIBRARIES}
    dl
)
#target_include_directories(app-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

