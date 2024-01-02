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
    std::string GetDefaultFontName() const;

private:
    std::unordered_map<std::string, Font> mFonts {};
    std::string mDefaultFontName {};
};

} // namespace pong
