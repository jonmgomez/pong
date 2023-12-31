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
    Text(const std::string&, const std::string& path, float scale, int pixelLineHeight = 128);

    std::vector<OffsetGraphic> GetRenderables() override;
    BaseComponent* GetBaseComponent() override;

    std::string GetText() const;
    void SetText(const std::string& text);
    void SetScale(float scale);
    void SetPixelLineHeight(int pixelLineHeight);
    void SetColor(GLRGBAColor color);
    void RecomputeText();

    std::string mText { "" };
    float mScale { 1.0f };
    int mPixelLineHeight { 128 };

private:
    std::vector<TextCharacter> mCharacters {};
    std::string mFontPath { "D:/code/pong/assets/pixeloid.ttf" };
    GLRGBAColor mColor { GLRGBA_WHITE };
};

} // namespace pong
