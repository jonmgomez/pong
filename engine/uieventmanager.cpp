#include "uieventmanager.h"

#include "button.h"
#include "checkbox.h"
#include "colliderbox.h"
#include "logger.h"
#include "input.h"
#include "slider.h"
#include "uielement.h"

namespace pong
{

void UIEventManager::VisitButton(Button& button)
{
    const glm::vec3 mousePosition = Input::GetMousePosition();
    const bool inBounds = button.GetColliderBox()->CheckPointInBounds(mousePosition);
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

void UIEventManager::VisitCheckBox(CheckBox& checkBox)
{
    const glm::vec3 mousePosition = Input::GetMousePosition();
    if (checkBox.GetColliderBox()->CheckPointInBounds(mousePosition) && Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT) == InputState::Pressed)
    {
        checkBox.OnClick();
    }
}

void UIEventManager::VisitSlider(Slider& slider)
{
    const glm::vec3 mousePosition = Input::GetMousePosition();
    const bool inBounds = slider.GetColliderBox()->CheckPointInBounds(mousePosition);
    const bool mousePressed = Input::CheckMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);

    if ((inBounds && mousePressed) || (mousePressed && slider.WasPressed()))
    {
        slider.OnMouseDown(mousePosition);
    }
    else if (!mousePressed && slider.WasPressed())
    {
        slider.OnMouseReleased();
    }
}

void UIEventManager::VisitText(Text& /*text*/)
{
    // No events to process on text objects
}

void UIEventManager::ProcessEvents(const UIElementCollection& uiElements)
{
    for (auto& uiElement : uiElements)
    {
        uiElement->Accept(*this);
    }
}

} // namespace pong
