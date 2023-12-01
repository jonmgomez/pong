#include "button.h"

#include "pong.h"
#include "uielement.h"

namespace pong
{

Button::Button(float width, float height) :
    mRectangle(width, height)
{
    mColliderBox.Resize(width, height);
}

void Button::Render() const
{
    mRectangle.Draw(mPosition);
}

UIElementType Button::GetType() const
{
    return UIElementType::Button;
}

void Button::AddListener(ButtonEvent event, std::function<void()> callback)
{
    ASSERT(event < ButtonEvent::EVENTS_COUNT);
    mListeners.at(static_cast<int>(event)).emplace_back(callback);
}

void Button::OnEvent(ButtonEvent event)
{
    switch (event)
    {
        case ButtonEvent::Pressed:
            mPressed = true;
            break;
        case ButtonEvent::Release:
            mPressed = false;
            break;
        case ButtonEvent::Hover:
            mHovered = true;
            break;
        case ButtonEvent::Unhover:
            mHovered = false;
            break;
    }

    const auto& listeners = mListeners.at(static_cast<int>(event));
    for (auto& callback : listeners)
    {
        callback();
    }
}

void Button::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    mColliderBox.OnPositionUpdate(position);
}

void Button::Resize(float width, float height)
{
    mRectangle.Resize(width, height);
    mColliderBox.Resize(width, height);
}

ColliderBox* Button::GetColliderBox()
{
    return &mColliderBox;
}

bool Button::IsPressed() const
{
    return mPressed;
}

bool Button::IsHovered() const
{
    return mHovered;
}

} // namespace pong
