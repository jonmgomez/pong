#pragma once

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
    static const int GetID(bool newInstance = false)
    {
        static int instanceCount = 0;
        static const int idCounter = sID++;

        return idCounter + (newInstance ? instanceCount++ : 0);
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

template<typename T> std::vector<std::unique_ptr<T>> Component<T>::mComponents {};

class BaseComponent
{
public:
    virtual ~BaseComponent() = default;

    int GetGameObjectID() const;
    void SetGameObjectID(int gameObjectID);
    GameObject* GetGameObject() const;
    void SetGameObject(GameObject* gameObject);

private:
    int mGameObjectID { 0 };
    GameObject* mGameObject { nullptr };
};

} // namespace pong
