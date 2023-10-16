cmake_minimum_required(VERSION 3.21)

project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCES
    main.cpp
    indexbuffer.cpp
    renderer.cpp
    shader.cpp
    vertexarray.cpp
    vertexbuffer.cpp
    vertexbufferlayout.cpp
)

add_executable(pong ${SOURCES})

add_subdirectory(glfw-3.3.8)
add_subdirectory(glew-2.1.0)

include_directories(glfw-3.3.8/include)

target_link_libraries(pong glfw)
target_link_libraries(pong opengl32)
target_link_libraries(pong glew)

# I would use /Wall here but unfortunately the msvc headers trigger some pedantic warnings,
# and I would like to keep /WX as well. Since I don't have an easy way to ignore the warnings
# for the system libraries, just use /W4. Seems like /Wall has some weird extra warnings anyways.
target_compile_options(pong PRIVATE /W4 /WX)

target_compile_definitions(pong PRIVATE
    $<$<CONFIG:Debug>:
        DEBUG=1
    >
)
