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
    Pong::GetInstance().GetComponentManager().UpdateUIComponentOrderLayers();
}

} // namespace pong
