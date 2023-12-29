#include "componentmanager.h"

namespace pong
{

void ComponentManager::Reset()
{
    mUIComponents.clear();
}

const std::vector<UIElement*>& ComponentManager::GetUIComponents() const
{
    return mUIComponents;
}

void ComponentManager::UpdateUIElementOrderLayers()
{
    std::sort(mUIComponents.begin(), mUIComponents.end(), [](UIElement* a, UIElement* b) {
        return a->GetOrderLayer() < b->GetOrderLayer();
    });
}

} // namespace pong
