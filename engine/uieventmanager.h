#pragma once

#include "uielement.h"

#include <memory>
#include <vector>

namespace pong
{

using UIElementCollection = std::vector<std::unique_ptr<UIElement>>;

class UIEventManager
{
public:
    void ProcessEvents(const UIElementCollection& uiElements);
};

} // namespace pong
