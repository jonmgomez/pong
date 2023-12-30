#pragma once

#include "button.h"
#include "checkbox.h"
#include "slider.h"
#include "text.h"
#include "uicomponent.h"

#include <memory>
#include <vector>

namespace pong
{

class UIEventManager
{
public:
    void ProcessEvents();

private:
    void Process(Button& button) const;
    void Process(CheckBox& checkBox) const;
    void Process(Slider& slider) const;
    void Process(Text& text) const;

    bool CheckMouseInComponentBounds(BaseComponent& component, RectangleBounds bounds) const;
    bool CheckMouseInBounds(const RectangleBounds& bounds) const;
};

} // namespace pong
