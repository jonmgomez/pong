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
    static int sId;

    int mId { sId++ };

protected:
    std::unique_ptr<Mesh>mMesh { nullptr };
    std::unique_ptr<ColliderBox>mColliderBox { nullptr };
    glm::vec3 mPosition { glm::vec3(0.0f) };
    std::string mName { "" };

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnCollisionStart(GameObject& other);
    virtual void OnCollisionStay(GameObject& other);
    virtual void OnCollisionStop(GameObject& other);

    int GetId() const;
    ColliderBox* GetColliderBox() const;
    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    const std::string& GetName() const;
    void SetName(const std::string& name);

    bool CheckForCollision(GameObject& other);

    void Render() const;
};

} // namespace pong
