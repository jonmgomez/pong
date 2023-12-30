set(SOURCES
    applicationwindow.cpp
    collisionmanager.cpp
    componentmanager.cpp
    engine.cpp
    input.cpp
    pong.cpp
    pongscenes.cpp
    random.cpp
    renderer.cpp
    sceneloader.cpp
    timer.cpp
    uieventmanager.cpp
)

add_library(engine ${SOURCES})

add_subdirectory(audio)
add_subdirectory(graphics)
add_subdirectory(logger)
add_subdirectory(settings)

target_link_libraries(engine
    PUBLIC
        compile_flags
        render
        gameobjects
        components
        audio
        logger
        graphics
        settings
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
