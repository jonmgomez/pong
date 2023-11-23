#pragma once

#include "textcharacter.h"

#include <string>
#include <vector>

namespace pong
{

class Text
{
public:
    Text(const std::string&, const std::string& path, float size, int pixelLineHeight = 128);

    void CreateText();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void SetText(const std::string& text);

    void Render();

private:
    glm::vec3 mPosition { 0.0f };
    std::vector<TextCharacter> mCharacters {};
    std::string mText { "" };
    std::string mFontPath { "" };
    float mSize { 0.0f };
    int mPixelLineHeight { 0 };
};

} // namespace pong
