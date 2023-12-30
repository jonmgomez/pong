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
    void SetColor(GLRGBAColor color);

private:
    void CreateText();

    std::string mText { "" };
    std::vector<TextCharacter> mCharacters {};
    std::string mFontPath { "D:/code/pong/assets/pixeloid.ttf" };
    float mScale { 1.0f };
    int mPixelLineHeight { 128 };
};

} // namespace pong
