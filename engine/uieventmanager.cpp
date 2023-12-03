#include "uieventmanager.h"

#include "button.h"
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
            if (button.GetColliderBox()->CheckPointInBounds(mousePosition))
            {
                if (!button.WasHovered())
                {
                    button.OnEvent(ButtonEvent::Hover);
                }

                if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                {
                    if (!button.WasPressed())
                    {
                        button.OnEvent(ButtonEvent::Pressed);
                    }
                }
                else if (button.WasPressed())
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
        case UIElementType::Slider:
        {
            //LogInfo("Slider");
            auto& slider = static_cast<Slider&>(*uiElement);

            const bool inBounds = slider.GetColliderBox()->CheckPointInBounds(mousePosition);
            const bool mousePressed = Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

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
