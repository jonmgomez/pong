#include "uielement.h"

namespace pong
{

void UIElement::Render() const
{
    mMesh.Draw(mPosition);
}

void UIElement::AddListener(UIEventType event, std::function<void()> callback)
{
    mListeners.at(static_cast<int>(event)).emplace_back(callback);
}

void UIElement::OnEvent(UIEventType event)
{
    const auto& listeners = mListeners.at(static_cast<int>(event));
    for (auto& callback : listeners)
    {
        callback();
    }
}

int UIElement::GetOrderLayer() const
{
    return mOrderLayer;
}

void UIElement::SetOrderLayer(int orderLayer)
{
    mOrderLayer = orderLayer;
    //Pong::UpdateUIElementOrderLayer(this);
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
