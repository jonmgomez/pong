set(SOURCES
    graphic.cpp
    indexbuffer.cpp
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
        compile_flags
        glfw
        opengl32
        glew
        glm
        spdlog
        nlohmann_json
        stb
    PRIVATE
        engine
)

target_include_directories(render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
