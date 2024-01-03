#pragma once

#include "font.h"

#include <unordered_map>

namespace pong
{

class FontBank
{
public:
    FontBank() = default;
    ~FontBank() = default;

    void LoadFonts();
    Font* GetFont(const std::string& fontName);
    Font* GetDefaultFont();

private:
    std::unordered_map<std::string, Font> mFonts {};
    Font* mDefaultFont { nullptr };
};

} // namespace pong
