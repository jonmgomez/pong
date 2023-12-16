#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace pong
{

class Behavior;
class Transform;

template<typename ComponentSubType>
int GetComponentTypeID()
{
    return TypeIDGenerator<BaseComponent>::GetID<ComponentSubType>();
}

template<class T>
class Component : public BaseComponent
{
public:
    virtual ~Component() = default;

    static void AddComponent(std::unique_ptr<T> component)
    {
        mComponents.push_back(std::move(component));
    }

    static const std::vector<std::unique_ptr<T>>& GetComponents()
    {
        return mComponents;
    }

    static std::vector<std::unique_ptr<T>> mComponents;
};

// template<>
// class Component<Behavior>
// {
// public:
//     virtual ~Component() = default;

//     static void AddComponent(std::unique_ptr<Behavior> component)
//     {
//         std::cout << "Component<Behavior>::AddComponent()" << std::endl;
//         mComponents.push_back(std::move(component));
//     }

//     static const std::vector<std::unique_ptr<Behavior>>& GetComponents()
//     {
//         return mComponents;
//     }

//     static std::vector<std::unique_ptr<Behavior>> mComponents;
// };

template<typename T> std::vector<std::unique_ptr<T>> Component<T>::mComponents {};

class BaseComponent
{
public:
    virtual ~BaseComponent() = default;

    int GetEntityID() const { return mEntityID; }
    void SetEntityID(int entityID) { mEntityID = entityID; }

private:
    int mEntityID { 0 };
};

} // namespace pong
