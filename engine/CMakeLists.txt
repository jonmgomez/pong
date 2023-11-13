set(SOURCES
    circle.cpp
    colliderbox.cpp
    collisionmanager.cpp
    input.cpp
    mesh.cpp
    pong.cpp
    realtimelogger.cpp
    rectangle.cpp
)

add_library(engine ${SOURCES})

target_link_libraries(engine
    PUBLIC
        render
        gameobjects
        fmt
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
