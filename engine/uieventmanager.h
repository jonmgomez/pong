#pragma once

#include "button.h"
#include "checkbox.h"
#include "slider.h"
#include "uielement.h"
#include "processeventvisitor.h"

#include <memory>
#include <vector>

namespace pong
{

using UIElementCollection = std::vector<std::unique_ptr<UIElement>>;

class UIEventManager : public ProcessEventVisitor
{
public:
    void VisitButton(Button& button) override;
    void VisitCheckBox(CheckBox& checkBox) override;
    void VisitSlider(Slider& slider) override;
    void VisitText(Text& text) override;

    void ProcessEvents(const UIElementCollection& uiElements);
};

} // namespace pong
