set(SOURCES
    circle.cpp
    rectangle.cpp
    textcharacter.cpp
)

add_library(graphics ${SOURCES})

target_link_libraries(graphics
    PUBLIC
        compile_flags
        engine
        render
)

target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
