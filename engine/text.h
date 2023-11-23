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
    Text(const std::string&, const std::string& path, const glm::vec3& scale, int pixelLineHeight = 128);

    void CreateText();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetScale() const;
    void SetScale(const glm::vec3& scale);
    void SetText(const std::string& text);

    void Render();

private:
    glm::vec3 mPosition { 0.0f };
    glm::vec3 mScale { 1.0f };
    std::vector<TextCharacter> mCharacters {};
    std::string mText { "" };
    std::string mFontPath { "" };
    int mPixelLineHeight { 0 };
};

} // namespace pong
