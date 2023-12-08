#pragma once

namespace pong
{

class Button;
class CheckBox;
class Slider;
class Text;

class ProcessEventVisitor
{
public:
    virtual void VisitButton(Button& button) = 0;
    virtual void VisitCheckBox(CheckBox& checkBox) = 0;
    virtual void VisitSlider(Slider& slider) = 0;
    virtual void VisitText(Text& text) = 0;
};

} // namespace pong
