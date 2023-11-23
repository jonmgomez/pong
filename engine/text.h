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

    void PrintSingleCharacter(const std::string& path, char c);
    void PrintString(const std::string& path, const std::string& str);

    void Render();

    glm::vec3 mPosition { 0.0f };

private:
    std::vector<std::unique_ptr<TextCharacter>> mCharacters {};
};

} // namespace pong
