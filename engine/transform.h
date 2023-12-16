#pragma once

#include "component.h"

#include <glm/glm.hpp>

namespace pong
{

class Transform : public Component<Transform>
{
public:
    Transform(glm::vec3 position) { mPosition = position; };

    glm::vec3 mPosition { 0.0f };
};

class Behaviour : public Component<Behaviour>
{
public:
    Behaviour() = default;
    virtual ~Behaviour() = default;

    virtual void OnStart()
    {
        std::cout << "Behaviour::OnStart()" << std::endl;
    }

    virtual void OnUpdate()
    {
        std::cout << "Behaviour::OnUpdate()" << std::endl;
    }

    virtual void OnCollisionStart() {}
    virtual void OnCollisionStay() {}
    virtual void OnCollisionStop() {}
};

class Test : public Behaviour
{
public:
    void OnStart() override
    {
        std::cout << "Test::OnStart()" << std::endl;
    }

    void OnUpdate() override
    {
        std::cout << "Test::OnUpdate()" << std::endl;
    }
};

} // namespace pong
