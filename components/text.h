#pragma once

#include "component.h"
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
    Text();
    Text(const std::string& text, const std::string& fontName, float scale);

    std::vector<OffsetGraphic> GetRenderables() override;
    BaseComponent* GetBaseComponent() override;

    std::string GetText() const;
    void SetText(const std::string& text);
    void SetFont(const std::string& fontName);
    void SetScale(float scale);
    void SetColor(GLRGBAColor color);
    void RecomputeText();

    std::string mText {};
    std::string mFont {};
    float mScale { 1.0f };

private:
    std::vector<TextCharacter> mCharacters {};
    std::string mFontPath {};
    GLRGBAColor mColor { GLRGBA_WHITE };
};

} // namespace pong
