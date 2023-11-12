#pragma once

#include "colliderbox.h"
#include "mesh.h"
#include "utils.h"

#include <glm/glm.hpp>

#include <memory>

namespace pong
{

class GameObject
{
private:
    static int sId;

    int mId { sId++ };
    glm::vec3 mPosition { glm::vec3(0.0f) };
    std::string mInstanceName { "" };

protected:
    std::unique_ptr<Mesh>mMesh { nullptr };
    std::unique_ptr<ColliderBox>mColliderBox { nullptr };

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
    std::string GetInstanceName() const;
    void SetInstanceName(const std::string& name);

    bool CheckForCollision(GameObject& other);

    void Render() const;
    template <typename T>
    T* GetObject()
    {
        return dynamic_cast<T*>(this);
    }
};

} // namespace pong
