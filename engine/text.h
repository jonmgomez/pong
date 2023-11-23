#pragma once

#include "textcharacter.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace pong
{

class Text
{
public:
    Text(const std::string&, const std::string& path, float scale, int pixelLineHeight = 128);

    void CreateText();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    std::string GetText() const;
    void SetText(const std::string& text);

    void Render();

private:
    std::string mText { "" };
    std::vector<TextCharacter> mCharacters {};
    std::string mFontPath { "" };
    glm::vec3 mPosition { 0.0f };
    float mScale { 1.0f };
    int mPixelLineHeight { 0 };
};

} // namespace pong
