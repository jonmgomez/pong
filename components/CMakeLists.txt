set(SOURCES
    behavior.cpp
    button.cpp
    checkbox.cpp
    colliderbox.cpp
    component.cpp
    mesh.cpp
    slider.cpp
    text.cpp
    uicomponent.cpp
)

add_library(components ${SOURCES})

target_link_libraries(components
    PUBLIC
        compile_flags
        engine
        gameobjects
        logger
        graphics
        audio
)

target_include_directories(components
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
