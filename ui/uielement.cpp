#include "uielement.h"

#include "componentmanager.h"
#include "pong.h"

namespace pong
{

int UIElement::GetOrderLayer() const
{
    return mOrderLayer;
}

void UIElement::SetOrderLayer(int orderLayer)
{
    mOrderLayer = orderLayer;
    Pong::GetInstance().GetComponentManager().UpdateUIElementOrderLayers();
}

} // namespace pong
