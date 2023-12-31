#include "uimenu.h"

namespace pong
{

static constexpr GLRGBAColor IDLE_TEXT_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
static constexpr GLRGBAColor HOVER_TEXT_COLOR = { 0.4f, 0.4f, 0.4f, 1.0f };
static constexpr float BUTTON_HOVER_SCALE = 1.35f;

void UIMenu::SetupButton(Button* button, Text* buttonText)
{
    const float buttonWidth = button->GetWidth();
    const float buttonHeight = button->GetHeight();

    button->AddListener(ButtonEvent::Hover, [button, buttonText, buttonWidth, buttonHeight, this]() {
        this->ButtonHoverAnimation(button, buttonText, buttonWidth * BUTTON_HOVER_SCALE, buttonHeight * BUTTON_HOVER_SCALE);
    });

    button->AddListener(ButtonEvent::Unhover, [button, buttonText, buttonWidth, buttonHeight, this]() {
       this->ButtonUnhoverAnimation(button, buttonText, buttonWidth, buttonHeight);
    });
}

void UIMenu::ButtonHoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(HOVER_TEXT_COLOR);
}

void UIMenu::ButtonUnhoverAnimation(Button* button, Text* buttonText, float newWidth, float newHeight)
{
    button->Resize(newWidth, newHeight);
    buttonText->SetColor(IDLE_TEXT_COLOR);
}

} // namespace pong