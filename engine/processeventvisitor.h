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
    virtual void Visit(Button& button) = 0;
    virtual void Visit(CheckBox& checkBox) = 0;
    virtual void Visit(Slider& slider) = 0;
    virtual void Visit(Text& text) = 0;
};

} // namespace pong
