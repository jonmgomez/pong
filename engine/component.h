#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace pong
{

class GameObject;

template <typename BaseClass>
class TypeIDGenerator
{
public:
    template<class SubClass>
    static const int GetID()
    {
        static const int idCounter = sID++;
        return idCounter;
    }

private:
    static int sID;
};

template<typename T> int TypeIDGenerator<T>::sID = 0;

template<typename ComponentSubType>
int GetComponentTypeID()
{
    return TypeIDGenerator<BaseComponent>::GetID<ComponentSubType>();
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

    int GetGameObjectID() const;
    void SetGameObjectID(int gameObjectID);
    GameObject* GetGameObject() const;
    void SetGameObject(GameObject* gameObject);

    template<typename T>
    T* GetComponent()
    {
        return mGameObject->GetComponent<T>();
    }

private:
    int mGameObjectID { 0 };
    GameObject* mGameObject { nullptr };
};

} // namespace pong
