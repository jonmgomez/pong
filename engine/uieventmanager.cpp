#include "uieventmanager.h"

#include "button.h"
#include "colliderbox.h"
#include "logger.h"
#include "input.h"
#include "uielement.h"

namespace pong
{

void UIEventManager::ProcessEvents(const std::vector<std::unique_ptr<UIElement>>& uiElements)
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
            if (!button.IsHovered())
            {
                button.OnEvent(UIEventType::Hover);
            }

            if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                if (!button.IsPressed())
                {
                    button.OnEvent(UIEventType::Pressed);
                }
            }
            else if (button.IsPressed())
            {
                button.OnEvent(UIEventType::Release);
            }
        }
        else if (button.IsHovered())
        {
            button.OnEvent(UIEventType::Unhover);
        }
    }
}

} // namespace pong
