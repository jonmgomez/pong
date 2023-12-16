#pragma once

#include "component.h"
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

    virtual void InitalizeComponents() {};
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

    template<typename T>
    T* GetComponent()
    {
        const int componentID = GetComponentTypeID<T>();

        std::cout << mComponents.size() << " id: " << componentID << std::endl;

        auto iterator = mComponents.find(componentID);
        if (iterator != mComponents.end())
        {
            std::cout << "found" << std::endl;
            return static_cast<T*>(mComponents[componentID]);
        }

        return nullptr;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetGameObject(this);
        component->SetGameObjectID(mId);

        const int componentID = GetComponentTypeID<T>();
        mComponents.insert(std::make_pair(componentID, component.get()));
        T::AddComponent(std::move(component));

        return component.get();
    }

protected:
    std::unique_ptr<Mesh> mMesh {};
    std::unique_ptr<ColliderBox> mColliderBox {};
    std::unordered_map<int, BaseComponent*> mComponents {};

private:
    static int sId;

    int mId { sId++ };
    glm::vec3 mPosition { glm::vec3(0.0f) };
    std::string mInstanceName { "" };
};

} // namespace pong
