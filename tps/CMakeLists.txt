include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

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

FetchContent_Declare(spdlog
    URL ${CMAKE_SOURCE_DIR}/tps/spdlog-1.12.0.zip
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(fmt
    URL ${CMAKE_SOURCE_DIR}/tps/fmt-10.1.1.zip
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(concurrentqueue
    URL ${CMAKE_SOURCE_DIR}/tps/concurrentqueue-1.0.4.zip
)
FetchContent_MakeAvailable(concurrentqueue)

FetchContent_Declare(stb
    URL ${CMAKE_SOURCE_DIR}/tps/stb-master.zip
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(stb)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

FetchContent_Declare(portaudio
    URL ${CMAKE_SOURCE_DIR}/tps/portaudio-19.7.0.zip
)
FetchContent_MakeAvailable(portaudio)

FetchContent_Declare(audiofile
    URL ${CMAKE_SOURCE_DIR}/tps/AudioFile-1.1.1.zip
)
FetchContent_MakeAvailable(audiofile)
