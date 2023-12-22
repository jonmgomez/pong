#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace pong
{

class GameObject;

template <typename BaseClass>
class TypeIdGenerator
{
public:
    template<class SubClass>
    static const int GetId()
    {
        static const int idCounter = sId++;
        return idCounter;
    }

private:
    static int sId;
};

template<typename T> int TypeIdGenerator<T>::sId = 0;

template<typename ComponentSubType>
int GetComponentTypeId()
{
    return TypeIdGenerator<BaseComponent>::GetId<ComponentSubType>();
}

template<class Derived>
class Component : public BaseComponent
{
public:
    virtual ~Component() = default;

    void Destroy() override
    {
        Derived::RemoveComponent(this);
    }

    static void AddComponent(std::unique_ptr<Derived> component)
    {
        mComponents.push_back(std::move(component));
    }

    static void RemoveComponent(Component<Derived>* component)
    {
        mComponents.erase(std::remove_if(mComponents.begin(), mComponents.end(), [component](const auto& componentPtr)
        {
            return componentPtr.get() == component;
        }));
    }

    static const std::vector<std::unique_ptr<Derived>>& GetComponents()
    {
        return mComponents;
    }

    static std::vector<std::unique_ptr<Derived>> mComponents;
};

template<typename Derived> std::vector<std::unique_ptr<Derived>> Component<Derived>::mComponents {};

class BaseComponent
{
public:
    virtual ~BaseComponent() = default;

    virtual void Destroy() = 0;

    GameObject* GetGameObject() const;
    void SetGameObject(GameObject* gameObject);
    int GetGameObjectId() const;

    template<typename T>
    T* GetComponent()
    {
        return mGameObject->GetComponent<T>();
    }

private:
    GameObject* mGameObject { nullptr };
};

} // namespace pong
