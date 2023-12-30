set(SOURCES
    audiomixer.cpp
    playingsound.cpp
    sound.cpp
)

add_library(audio ${SOURCES})

target_link_libraries(audio
    PUBLIC
        compile_flags
        engine
        concurrentqueue
        portaudio_static
        AudioFile
)

target_include_directories(audio
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
