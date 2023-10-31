#pragma once

#include "colliderbox.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <memory>

namespace pong
{

class GameObject
{
private:
    glm::vec3 mPosition { glm::vec3(0.0f) };

protected:
    std::unique_ptr<Mesh>mMesh { nullptr };
    std::unique_ptr<ColliderBox>mColliderBox { nullptr };

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnCollision(GameObject& other);

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void UpdateColliderBoxPosition() const;
    bool CheckForCollision(GameObject& other);

    void Render() const;

    ColliderBox* GetColliderBox() const { return mColliderBox.get(); }
};

} // namespace pong
