#pragma once

#include "mesh.h"

#include <glm/glm.hpp>

#include <memory>

namespace pong
{

class GameObject
{
private:
    static int sId;

    int mId { sId++ };

protected:
    std::unique_ptr<Mesh>mMesh { nullptr };
    std::string mName { "" };

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void OnStart();
    virtual void OnUpdate();

    int GetId() const;
    void SetName(const std::string& name);
    const std::string& GetName() const;
    void Render();

    glm::vec3 mPosition { glm::vec3(0.0f) };
};

} // namespace pong
