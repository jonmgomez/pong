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

} // namespace pong
