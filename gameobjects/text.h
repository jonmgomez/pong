#pragma once

#include <string>

namespace pong
{

class Text
{
public:
    Text(const std::string&, const std::string& path, int size);

private:
    std::vector<TextCharacter> mCharacters {};
};

} // namespace pong
