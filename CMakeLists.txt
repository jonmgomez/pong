cmake_minimum_required(VERSION 3.21)

project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_executable(pong main.cpp glad.c)

include_directories(glfw-3.3.8/include)
include_directories(glad/include)

target_link_libraries(pong ${PROJECT_SOURCE_DIR}/glfw3.lib)
target_link_libraries(pong opengl32)