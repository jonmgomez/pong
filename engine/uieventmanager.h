#pragma once

#include "uielement.h"

#include <memory>
#include <vector>

namespace pong
{

class UIEventManager
{
public:
    void ProcessEvents(const std::vector<std::unique_ptr<UIElement>>& uiElements);
};

} // namespace pong
