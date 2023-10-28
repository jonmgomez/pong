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

    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    void Render();

    glm::vec3 mPosition { glm::vec3(0.0f) };
};
