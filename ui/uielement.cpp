#include "uielement.h"

#include "pong.h"

namespace pong
{

void UIElement::Render() const
{
}

int UIElement::GetOrderLayer() const
{
    return mOrderLayer;
}

void UIElement::SetOrderLayer(int orderLayer)
{
    mOrderLayer = orderLayer;
    Pong::UpdateUIElementOrderLayer();
}

glm::vec3 UIElement::GetPosition() const
{
    return mPosition;
}

void UIElement::SetPosition(const glm::vec3& position)
{
    mPosition = position;
}

} // namespace pong
