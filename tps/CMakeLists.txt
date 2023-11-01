include(FetchContent)

FetchContent_Declare(glfw
    URL ${CMAKE_SOURCE_DIR}/tps/glfw-3.3.8.zip
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glew
    URL ${CMAKE_SOURCE_DIR}/tps/glew-2.1.0.zip
)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(glm
    URL ${CMAKE_SOURCE_DIR}/tps/glm-0.9.9.8.zip
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(nlohmann_json
    URL ${CMAKE_SOURCE_DIR}/tps/json-3.11.2.zip
)
FetchContent_MakeAvailable(nlohmann_json)
