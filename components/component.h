#pragma once

#include <algorithm>
#include <functional>
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

class ComponentDeserializer;

class BaseComponent
{
public:
    virtual ~BaseComponent() = default;

    virtual int GetTypeId() const = 0;
    virtual void Destroy() = 0;
    virtual void Accept(ComponentDeserializer& visitor) = 0;

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

template<class Derived>
class Component : public BaseComponent
{
public:
    virtual ~Component() = default;

    int GetTypeId() const override;
    void Destroy() override;
    void Accept(ComponentDeserializer& visitor) override;

    static void AddComponent(std::unique_ptr<Derived> component);
    static void RemoveComponent(Component<Derived>* component);
    static const std::vector<std::unique_ptr<Derived>>& GetComponents();
    static void SortComponents(std::function<bool(const Derived&, const Derived&)> compare);

    static std::vector<std::unique_ptr<Derived>> mComponents;
};

template<typename Derived> std::vector<std::unique_ptr<Derived>> Component<Derived>::mComponents {};

} // namespace pong

// Required for template instantiation
#include "componentdeserializer.h"

namespace pong
{

template<typename Derived>
int Component<Derived>::GetTypeId() const
{
    return GetComponentTypeId<Derived>();
}

template<typename Derived>
void Component<Derived>::Destroy()
{
    Derived::RemoveComponent(this);
}

template<typename Derived>
void Component<Derived>::Accept(ComponentDeserializer& visitor)
{
    visitor.VisitComponent(static_cast<Derived*>(this));
}

template<typename Derived>
void Component<Derived>::AddComponent(std::unique_ptr<Derived> component)
{
    mComponents.push_back(std::move(component));
}

template<typename Derived>
void Component<Derived>::RemoveComponent(Component<Derived>* component)
{
    mComponents.erase(std::remove_if(mComponents.begin(), mComponents.end(), [component](const auto& componentPtr)
    {
        return componentPtr.get() == component;
    }));
}

template<typename Derived>
const std::vector<std::unique_ptr<Derived>>& Component<Derived>::GetComponents()
{
    return mComponents;
}

template<typename Derived>
void Component<Derived>::SortComponents(std::function<bool(const Derived&, const Derived&)> compare)
{
    std::sort(mComponents.begin(), mComponents.end(), compare);
}


}
