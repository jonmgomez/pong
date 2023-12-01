#pragma once

#include "colliderbox.h"
#include "mesh.h"
#include "sound.h"
#include "utils.h"

#include <glm/glm.hpp>

#include <chrono>
#include <functional>
#include <memory>

namespace pong
{

class GameObject
{
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
    void SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback);
    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);

    void Render() const;
    template <typename T>
    T* GetObject()
    {
        return dynamic_cast<T*>(this);
    }

protected:
    std::unique_ptr<Mesh>mMesh { nullptr };
    std::unique_ptr<ColliderBox>mColliderBox { nullptr };

private:
    static int sId;

    int mId { sId++ };
    glm::vec3 mPosition { glm::vec3(0.0f) };
    std::string mInstanceName { "" };
};

} // namespace pong
