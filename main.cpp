#include "engine.h"
#include "logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

using namespace pong;

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    if (argc != 2)
    {
        LogError("Usage: {} <json_file_path>", argv[0]);
        return -1;
    }

    Engine engine;

    globals::engine::SetEngineInstance(&engine);

    engine.Init(argv[1]);
    engine.RunApplication();
    engine.Cleanup();

    globals::engine::SetEngineInstance(nullptr);

    return 0;
}
