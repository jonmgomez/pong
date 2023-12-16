#include "componentmanager.h"

namespace pong
{

template<typename ComponentSubType>
void ComponentManager::AddComponent(std::unique_ptr<ComponentSubType> component)
{
    static_assert(false);
}

template<typename ComponentSubType>
const std::vector<std::unique_ptr<ComponentSubType>>& ComponentManager::GetComponents()
{
    static_assert(false);
}

// template<>
// void ComponentManager::AddComponent<ColliderBox>(std::unique_ptr<ColliderBox> component)
// {
//     mCompColliderBoxes.emplace_back(std::move(component));
// }

// template<>
// const std::vector<std::unique_ptr<ColliderBox>>& ComponentManager::GetComponents<ColliderBox>()
// {
//     return mCompColliderBoxes;
// }

// template<>
// void ComponentManager::AddComponent<Transform>(std::unique_ptr<Transform> component)
// {
//     mCompTransforms.emplace_back(std::move(component));
// }

// template<>
// const std::vector<std::unique_ptr<Transform>>& ComponentManager::GetComponents<Transform>()
// {
//     return mCompTransforms;
// }

// template<>
// void ComponentManager::AddComponent<Behaviour>(std::unique_ptr<Behaviour> component)
// {
//     mCompBehaviours.emplace_back(std::move(component));
// }

// template<>
// const std::vector<std::unique_ptr<Behaviour>>& ComponentManager::GetComponents<Behaviour>()
// {
//     return mCompBehaviours;
// }

// template<>
// void ComponentManager::AddComponent<Test>(std::unique_ptr<Test> component)
// {
//     mCompBehaviours.emplace_back(std::move(component));
// }

// template<>
// const std::vector<std::unique_ptr<Test>>& ComponentManager::GetComponents<Test>()
// {
//     return mCompBehaviours;
// }

} // namespace pong
