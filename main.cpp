#include "main.h"

#include "engine.h"
#include "config.h"
#include "difficulty.h"
#include "input.h"
#include "pong.h"
#include "renderer.h"
#include "renderutils.h"
#include "timer.h"
#include "logger.h"
#include "utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

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

    Engine::GetInstance().Init(argv[1]);
    Engine::GetInstance().RunApplication();

    return 0;
}
