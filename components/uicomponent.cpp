#include "uicomponent.h"

#include "componentmanager.h"
#include "pong.h"

namespace pong
{

int UIComponent::GetOrderLayer() const
{
    return mOrderLayer;
}

void UIComponent::SetOrderLayer(int orderLayer)
{
    mOrderLayer = orderLayer;
    globals::game::GetPongInstance()->GetComponentManager().UpdateUIComponentOrderLayers();
}

} // namespace pong
