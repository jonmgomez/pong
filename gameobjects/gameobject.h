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

    virtual void InitalizeComponents() = 0;
    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnCollisionStart(GameObject& other);
    virtual void OnCollisionStay(GameObject& other);
    virtual void OnCollisionStop(GameObject& other);

    int GetID() const;
    std::string GetInstanceName() const;
    void SetInstanceName(const std::string& name);

    void SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback);
    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);

    template <typename T>
    T* GetObject()
    {
        return dynamic_cast<T*>(this);
    }

    template<typename T>
    T* GetComponent()
    {
        const int componentID = GetComponentTypeID<T>();

        auto iterator = mComponents.find(componentID);
        if (iterator != mComponents.end())
        {
            return static_cast<T*>(mComponents[componentID]);
        }

        return nullptr;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetGameObject(this);
        component->SetGameObjectID(mId);

        const int componentID = GetComponentTypeID<T>();
        mComponents.insert(std::make_pair(componentID, component.get()));
        T::AddComponent(std::move(component));

        return component.get();
    }

private:
    static int sId;

    int mId { sId++ };
    std::unordered_map<int, BaseComponent*> mComponents {};
    std::string mInstanceName { "" };
};

} // namespace pong
