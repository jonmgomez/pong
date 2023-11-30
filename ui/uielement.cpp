#include "uielement.h"

#include "pong.h"

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
    switch (event)
    {
        case UIEventType::Pressed:
            mPressed = true;
            break;
        case UIEventType::Release:
            mPressed = false;
            break;
        case UIEventType::Hover:
            mHovered = true;
            break;
        case UIEventType::Unhover:
            mHovered = false;
            break;
    }

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
    Pong::UpdateUIElementOrderLayer();
}

glm::vec3 UIElement::GetPosition() const
{
    return mPosition;
}

void UIElement::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    if (mColliderBox != nullptr)
    {
        mColliderBox->OnPositionUpdate(position);
    }
}

ColliderBox* UIElement::GetColliderBox() const
{
    return mColliderBox.get();
}

void UIElement::SetColliderBox(float width, float height)
{
    if (mColliderBox == nullptr)
    {
        mColliderBox = std::make_unique<ColliderBox>(width, height);
    }
    else
    {
        mColliderBox->SetWidth(width);
        mColliderBox->SetHeight(height);
    }
}

bool UIElement::IsPressed() const
{
    return mPressed;
}

bool UIElement::IsHovered() const
{
    return mHovered;
}

} // namespace pong
