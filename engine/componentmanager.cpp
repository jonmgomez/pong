#include "componentmanager.h"

namespace pong
{

void ComponentManager::Reset()
{
    mUIComponents.clear();
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
