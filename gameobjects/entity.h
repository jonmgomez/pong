#pragma once

#include "component.h"

#include <memory>
#include <vector>
#include <unordered_map>

namespace pong
{

template <typename BaseClass>
class TypeIDGenerator
{
public:
    template<class SubClass>
    static const int GetID(bool newInstance = false)
    {
        static int instanceCount = 0;
        static const int idCounter = mID++;

        return idCounter + (newInstance ? instanceCount++ : 0);
    }

private:
    static int mID;
};

template<typename T> int TypeIDGenerator<T>::mID = 0;



class Entity
{
public:
    void Register()
    {
        mID = sID++;
    }

    template<typename ComponentSubType>
    ComponentSubType* GetComponent()
    {
        const int componentID = GetComponentTypeID<ComponentSubType>();

        std::cout << mComponents.size() << " id: " << componentID << std::endl;

        auto iterator = mComponents.find(componentID);
        if (iterator != mComponents.end())
        {
            std::cout << "found" << std::endl;
            return static_cast<ComponentSubType*>(mComponents[componentID]);
        }

        return nullptr;
    }

    template<typename ComponentSubType, typename... Args>
    ComponentSubType* AddComponent(Args&&... args)
    {
        std::unique_ptr<ComponentSubType> component = std::make_unique<ComponentSubType>(std::forward<Args>(args)...);
        component->SetEntityID(mID);

        const int componentID = GetComponentTypeID<ComponentSubType>();
        mComponents.insert(std::make_pair(componentID, component.get()));
        ComponentSubType::AddComponent(std::move(component));

        return component.get();
    }

private:
    static int sID;

    std::unordered_map<int, BaseComponent*> mComponents {};
    int mID { 0 };
};

int Entity::sID = 0;

} // namespace pong
