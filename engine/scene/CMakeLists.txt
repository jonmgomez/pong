set(SOURCES
    sceneloader.cpp
    componentdeserializer.cpp
)

add_library(scene ${SOURCES})

target_link_libraries(scene
    PUBLIC
        compile_flags
        engine
        components
        gameobjects
        graphics
        nlohmann_json::nlohmann_json
)

target_include_directories(scene
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
