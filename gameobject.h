#pragma once

#include "mesh.h"

#include <glm/glm.hpp>

#include <memory>

class GameObject
{
protected:
    std::unique_ptr<Mesh>mMesh { nullptr };

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void OnStart();
    virtual void OnUpdate();
    void Render();

    glm::vec3 mPosition { glm::vec3(0.0f) };
};
