#include "uieventmanager.h"

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
        if (uiElement->GetColliderBox() == nullptr)
        {
            continue;
        }

        if (uiElement->GetColliderBox()->CheckPointInBounds(mousePosition))
        {
            if (!uiElement->IsHovered())
            {
                uiElement->OnEvent(UIEventType::Hover);
            }

            if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                if (!uiElement->IsPressed())
                {
                    uiElement->OnEvent(UIEventType::Pressed);
                }
            }
            else if (uiElement->IsPressed())
            {
                uiElement->OnEvent(UIEventType::Release);
            }
        }
        else if (uiElement->IsHovered())
        {
            uiElement->OnEvent(UIEventType::Unhover);
        }
    }
}

} // namespace pong
