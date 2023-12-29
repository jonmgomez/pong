#include "button.h"

#include "pong.h"
#include "uielement.h"

namespace pong
{

Button::Button(float width, float height) :
    mRectangle{width, height},
    mBounds{width, height}
{
}

std::vector<OffsetGraphic> Button::GetRenderables()
{
    std::vector<OffsetGraphic> renderables {};
    renderables.emplace_back(mRectangle, glm::vec3(0.0f));
    return renderables;
}

BaseComponent* Button::GetBaseComponent()
{
    return this;
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

float Button::GetWidth() const
{
    return mRectangle.GetWidth();
}

float Button::GetHeight() const
{
    return mRectangle.GetHeight();
}

void Button::Resize(float width, float height)
{
    mRectangle.Resize(width, height);
    mBounds = {width, height};
}

RectangleBounds Button::GetBounds() const
{
    return mBounds;
}

bool Button::WasPressed() const
{
    return mPressed;
}

bool Button::WasHovered() const
{
    return mHovered;
}

} // namespace pong
