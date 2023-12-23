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
    void Visit(Button& button) override;
    void Visit(CheckBox& checkBox) override;
    void Visit(Slider& slider) override;
    void Visit(Text& text) override;

    void ProcessEvents(const UIElementCollection& uiElements);

private:
    bool CheckMouseInBounds(BaseComponent& component, RectangleBounds bounds) const;
};

} // namespace pong
