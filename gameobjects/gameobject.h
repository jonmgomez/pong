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


    int GetID() const;
    std::string GetInstanceName() const;
    void SetInstanceName(const std::string& name);

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

class GameObjectBlueprint : public GameObject
{
public:
    virtual void InitalizeComponents() = 0;
};

} // namespace pong
