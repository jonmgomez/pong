#include "main.h"

#include "engine.h"
#include "pong.h"
#include "logger.h"
#include "entity.h"
#include "transform.h"

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

    //Pong::AddComponent<Transform>(glm::vec3(0.0f));
    // Pong::GetInstance().GetComponentManager().AddComponentNew<Transform>(std::make_unique<Transform>(glm::vec3(0.0f, 159.0f, 32.1f)));
    // Pong::GetInstance().GetComponentManager().AddComponentNew<Transform>(std::make_unique<Transform>(glm::vec3(0.0f, 0.0f, 0.0f)));
    // Pong::GetInstance().GetComponentManager().AddComponentNew<Transform>(std::make_unique<Transform>(glm::vec3(50.0f)));
    // Pong::GetInstance().GetComponentManager().AddComponentNew<Transform>(std::make_unique<Transform>(glm::vec3(1000.0f, 0.0f, 2.1f)));
    // Pong::GetInstance().GetComponentManager().AddComponentNew<Transform>(std::make_unique<Transform>(glm::vec3(-11.0f, -132.0f, -2.1f)));


    // Entity test;
    // Transform* transform = test.AddComponent<Transform>(glm::vec3(10.0f));
    // (void)transform;
    // std::cout << "X: " << test.GetComponent<Transform>()->mPosition.x << std::endl;

    // const std::vector<std::unique_ptr<Transform>>& transforms = Pong::GetInstance().GetComponentManager().GetComponentsNew<Transform>();
    // for (auto& transform : transforms)
    // {
    //     std::cout << "Transform: " << transform->mPosition.x << ", " << transform->mPosition.y << ", " << transform->mPosition.z << std::endl;
    // }

    // Behaviour::AddComponent(std::make_unique<Behaviour>());
    // Test::AddComponent(std::make_unique<Test>());

    // // Pong::GetInstance().GetComponentManager().AddComponent<Behaviour>(std::make_unique<Behaviour>());
    // // Pong::GetInstance().GetComponentManager().AddComponent<Behaviour>(std::make_unique<Test>());
    // // Pong::GetInstance().GetComponentManager().AddComponent<Component>(std::make_unique<Component>());

    // const std::vector<std::unique_ptr<Behaviour>>& behaviours = Behaviour::GetComponents();
    // for (auto& behaviour : behaviours)
    // {
    //     behaviour->OnStart();
    //     behaviour->OnUpdate();
    // }

    Engine::GetInstance().Init(argv[1]);
    Engine::GetInstance().RunApplication();

    return 0;
}
