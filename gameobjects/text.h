#pragma once

#include "textcharacter.h"

#include <string>
#include <vector>

namespace pong
{

class Text
{
public:
    Text(const std::string&, const std::string& path, int size);

    void PrintSingleCharacter(const std::string& path, char c);
    void PrintString(const std::string& path, const std::string& str);

private:
    std::vector<TextCharacter> mCharacters {};
};

} // namespace pong
