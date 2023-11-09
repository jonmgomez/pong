set(SOURCES
    indexbuffer.cpp
    renderer.cpp
    renderutils.cpp
    shader.cpp
    texture.cpp
    vertexarray.cpp
    vertexbuffer.cpp
    vertexbufferlayout.cpp
)

add_library(render ${SOURCES})

target_link_libraries(render
    PUBLIC
        glfw
        opengl32
        glew
        glm
        spdlog
        nlohmann_json
        compile_flags
)

target_include_directories(render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
