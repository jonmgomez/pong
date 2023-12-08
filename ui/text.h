#pragma once

#include "textcharacter.h"
#include "uielement.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace pong
{

class Text : public UIElement
{
public:
    Text(const std::string&, const std::string& path, float scale, int pixelLineHeight = 128);

    std::string GetText() const;
    void SetText(const std::string& text);
    void SetColor(GLRGBAColor color);

    void Render() const override;
    void Accept(ProcessEventVisitor& visitor) override;

private:
    void CreateText();

    std::string mText { "" };
    std::vector<TextCharacter> mCharacters {};
    std::string mFontPath { "" };
    float mScale { 1.0f };
    int mPixelLineHeight { 0 };
};

} // namespace pong
