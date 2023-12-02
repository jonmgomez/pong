#include "uieventmanager.h"

#include "button.h"
#include "colliderbox.h"
#include "logger.h"
#include "input.h"
#include "uielement.h"

namespace pong
{

void UIEventManager::ProcessEvents(const UIElementCollection& uiElements)
{
    const glm::vec3 mousePosition = Input::GetMousePosition();

    for (auto& uiElement : uiElements)
    {
        if (uiElement->GetType() != UIElementType::Button)
        {
            continue;
        }

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
    }
}

} // namespace pong
