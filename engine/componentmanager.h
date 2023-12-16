#pragma once

#include "component.h"
#include "colliderbox.h"
#include "mesh.h"
#include "transform.h"
#include "utils.h"

#include <memory>
#include <vector>

namespace pong
{

class ComponentManager
{
public:
    template<typename ComponentSubType>
    void AddComponentNew(std::unique_ptr<ComponentSubType> component)
    {
        ComponentSubType::AddComponent(std::move(component));
    }

    template<typename ComponentSubType>
    const std::vector<std::unique_ptr<ComponentSubType>>& GetComponentsNew()
    {
        return ComponentSubType::GetComponents();
    }

    template<typename ComponentSubType>
    void AddComponent(std::unique_ptr<ComponentSubType> component);

    template<typename ComponentSubType>
    const std::vector<std::unique_ptr<ComponentSubType>>& GetComponents();


private:
    // std::vector<ComponentVector> mComponents {};
    // std::vector<std::unique_ptr<ColliderBox>> mCompColliderBoxes {};
    // std::vector<std::unique_ptr<Transform>> mCompTransforms {};
    // std::vector<std::unique_ptr<Behaviour>> mCompBehaviours {};
};

} // namespace pong
