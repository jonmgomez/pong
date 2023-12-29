#include "uieventmanager.h"

#include "button.h"
#include "checkbox.h"
#include "component.h"
#include "colliderbox.h"
#include "gameobject.h"
#include "logger.h"
#include "input.h"
#include "slider.h"
#include "transform.h"
#include "uielement.h"

namespace pong
{

void UIEventManager::Visit(Button& button)
{
    const bool inBounds = CheckMouseInComponentBounds(button, button.GetBounds());
    const InputState mouseButtonState = Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT);

    if (inBounds)
    {
        if (!button.WasHovered())
        {
            button.OnEvent(ButtonEvent::Hover);
        }

        if (mouseButtonState == InputState::Pressed)
        {
            button.OnEvent(ButtonEvent::Pressed);
        }
        else if (mouseButtonState == InputState::Released)
        {
            button.OnEvent(ButtonEvent::Release);
        }
    }
    else if (button.WasHovered())
    {
        button.OnEvent(ButtonEvent::Unhover);
    }
}

void UIEventManager::Visit(CheckBox& checkBox)
{
    const bool inBounds = CheckMouseInComponentBounds(checkBox, checkBox.GetBounds());
    const InputState mouseButtonState = Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT);

    if (inBounds && mouseButtonState == InputState::Pressed)
    {
        checkBox.OnClick();
    }
}

void UIEventManager::Visit(Slider& slider)
{
    const bool inBounds = CheckMouseInComponentBounds(slider, slider.GetBounds());
    const bool mousePressed = Input::CheckMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);

    if ((inBounds && mousePressed) || (mousePressed && slider.WasPressed()))
    {
        slider.OnMouseDown(Input::GetMousePosition());
    }
    else if (!mousePressed && slider.WasPressed())
    {
        slider.OnMouseReleased();
    }
}

void UIEventManager::Visit(Text& /*text*/)
{
    // No events to process on text objects
}

void UIEventManager::ProcessEvents(const std::vector<UIElement*>& uiElements)
{
    for (auto& uiElement : uiElements)
    {
        uiElement->Accept(*this);
    }
}

bool UIEventManager::CheckMouseInComponentBounds(BaseComponent& component, RectangleBounds bounds) const
{
    const Transform* transform = component.GetComponent<Transform>();
    if (transform != nullptr)
    {
        bounds = bounds + transform->mPosition;
    }

    return CheckMouseInBounds(bounds);
}

bool UIEventManager::CheckMouseInBounds(const RectangleBounds& bounds) const
{
    const glm::vec3 mousePosition = Input::GetMousePosition();
    return bounds.CheckPointInBounds(mousePosition);
}

} // namespace pong
