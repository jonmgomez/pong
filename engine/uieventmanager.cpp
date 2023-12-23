#include "uieventmanager.h"

#include "button.h"
#include "checkbox.h"
#include "colliderbox.h"
#include "logger.h"
#include "input.h"
#include "slider.h"
#include "transform.h"
#include "uielement.h"

namespace pong
{

void UIEventManager::Visit(Button& button)
{
    RectangleBounds bounds = button.GetBounds();
    bounds = bounds + button.GetPosition();
    const glm::vec3 mousePosition = Input::GetMousePosition();
    const bool inBounds = bounds.CheckPointInBounds(mousePosition);
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
    const glm::vec3 mousePosition = Input::GetMousePosition();
    RectangleBounds bounds = checkBox.GetBounds();
    bounds = bounds + checkBox.GetPosition();

    if (bounds.CheckPointInBounds(mousePosition) && Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT) == InputState::Pressed)
    {
        checkBox.OnClick();
    }
}

void UIEventManager::Visit(Slider& slider)
{
    RectangleBounds bounds = slider.GetBounds();
    bounds = bounds + slider.GetPosition();
    const glm::vec3 mousePosition = Input::GetMousePosition();
    const bool inBounds = bounds.CheckPointInBounds(mousePosition);
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

void UIEventManager::Visit(Text& /*text*/)
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

bool UIEventManager::CheckMouseInBounds(BaseComponent& component, RectangleBounds bounds) const
{
    const glm::vec3 mousePosition = Input::GetMousePosition();
    (void)component;

    // const Transform* transform = component.GetComponent<Transform>();
    // if (transform != nullptr)
    // {
    //     bounds = bounds + transform->mPosition;
    // }

    return bounds.CheckPointInBounds(mousePosition);
}

} // namespace pong
