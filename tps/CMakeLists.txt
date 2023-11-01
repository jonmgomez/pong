include(FetchContent)

FetchContent_Declare(nlohmann_json
    URL ${CMAKE_SOURCE_DIR}/tps/json-3.11.2.zip
)
FetchContent_MakeAvailable(nlohmann_json)
