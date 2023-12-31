#pragma once

#include "button.h"
#include "text.h"

namespace pong
{

class UIMenu
{
public:
    void SetupButton(Button* button, Text* buttonText);
    void ButtonHoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight);
    void ButtonUnhoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight);
};

} // namespace pong