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

void UIEventManager::ProcessEvents(const UIElementCollection& uiElements)
{
    const glm::vec3 mousePosition = Input::GetMousePosition();

    for (auto& uiElement : uiElements)
    {
        switch (uiElement->GetType())
        {
        case UIElementType::Button:
        {
            auto& button = static_cast<Button&>(*uiElement);

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
            break;
        }
        case UIElementType::CheckBox:
        {
            auto& checkBox = static_cast<CheckBox&>(*uiElement);
            if (checkBox.GetColliderBox()->CheckPointInBounds(mousePosition) && Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_LEFT) == InputState::Pressed)
            {
                checkBox.OnClick();
            }
            break;
        }
        case UIElementType::Slider:
        {
            auto& slider = static_cast<Slider&>(*uiElement);

            const bool inBounds = slider.GetColliderBox()->CheckPointInBounds(mousePosition);
            const bool mousePressed = Input::CheckMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);

            if ((inBounds && mousePressed) || (mousePressed && slider.WasPressed()))
            {
                slider.OnMouseHeld(mousePosition);
            }
            else if (!mousePressed && slider.WasPressed())
            {
                slider.OnMouseReleased();
            }
            break;
        }
        case UIElementType::Text:
            break;
        default:
            break;
        }
    }
}

} // namespace pong
