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
    std::string mTag {""};
    std::string mName {""};

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnCollisionStart(GameObject& other);
    virtual void OnCollisionStay(GameObject& other);
    virtual void OnCollisionEnd(GameObject& other);

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    std::string GetTag() const { return mTag; }
    std::string GetName() const { return mName; }
    void UpdateColliderBoxPosition() const;
    bool CheckForCollision(GameObject& other);

    void Render() const;

    ColliderBox* GetColliderBox() const { return mColliderBox.get(); }
};

} // namespace pong
