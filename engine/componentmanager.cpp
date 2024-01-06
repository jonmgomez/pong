#include "componentmanager.h"

#include "gameobject.h"

namespace pong
{

void ComponentManager::Reset()
{
    mUIComponents.erase(std::remove_if(mUIComponents.begin(), mUIComponents.end(), [](UIComponent* component) {
        return component->GetBaseComponent()->GetGameObject()->ShouldDestroyOnLoad();
    }), mUIComponents.end());
}

const std::vector<UIComponent*>& ComponentManager::GetUIComponents() const
{
    return mUIComponents;
}

void ComponentManager::UpdateUIComponentOrderLayers()
{
    std::sort(mUIComponents.begin(), mUIComponents.end(), [](UIComponent* a, UIComponent* b) {
        return a->GetOrderLayer() < b->GetOrderLayer();
    });
}

} // namespace pong
