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
#include "uicomponent.h"

namespace pong
{

void UIEventManager::ProcessEvents()
{
    for (auto& button : Button::GetComponents())
    {
        Process(*button);
    }

    for (auto& checkBox : CheckBox::GetComponents())
    {
        Process(*checkBox);
    }

    for (auto& slider : Slider::GetComponents())
    {
        Process(*slider);
    }

    for (auto& text : Text::GetComponents())
    {
        Process(*text);
    }
}

void UIEventManager::Process(Button& button) const
{
    const bool inBounds = CheckMouseInComponentBounds(button, button.GetBounds());
    const InputState mouseButtonState = globals::input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT);

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

void UIEventManager::Process(CheckBox& checkBox) const
{
    const bool inBounds = CheckMouseInComponentBounds(checkBox, checkBox.GetBounds());
    const InputState mouseButtonState = globals::input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT);

    if (inBounds && mouseButtonState == InputState::Pressed)
    {
        checkBox.OnClick();
    }
}

void UIEventManager::Process(Slider& slider) const
{
    const bool inBounds = CheckMouseInComponentBounds(slider, slider.GetBounds());
    const bool mousePressed = globals::input::CheckMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);

    if ((inBounds && mousePressed) || (mousePressed && slider.WasPressed()))
    {
        slider.OnMouseDown(globals::input::GetMousePosition());
    }
    else if (!mousePressed && slider.WasPressed())
    {
        slider.OnMouseReleased();
    }
}

void UIEventManager::Process(Text& /*text*/) const
{
    // No events to process on text objects
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
    const glm::vec3 mousePosition = globals::input::GetMousePosition();
    return bounds.CheckPointInBounds(mousePosition);
}

} // namespace pong
