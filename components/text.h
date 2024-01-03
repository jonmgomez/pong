#pragma once

#include "component.h"
#include "font.h"
#include "textcharacter.h"
#include "uicomponent.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace pong
{

class Text : public UIComponent, public Component<Text>
{
public:
    Text() = default;
    Text(const std::string& text, Font* font, float scale);

    std::vector<OffsetGraphic> GetRenderables() override;
    BaseComponent* GetBaseComponent() override;

    std::string GetText() const;
    void SetText(const std::string& text);
    void SetFont(Font* font);
    void SetScale(float scale);
    void SetColor(GLRGBAColor color);
    void RecomputeText();

    std::string mText {};
    Font* mFont { nullptr };
    float mScale { 1.0f };

private:
    std::vector<TextCharacter> mCharacters {};
    GLRGBAColor mColor { GLRGBA_WHITE };
};

} // namespace pong
