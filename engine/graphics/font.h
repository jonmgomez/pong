#pragma once

#include "image.h"

#include <stb_truetype.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace pong
{

using image::Image;

// Represents a single character in a font, including offsets and its bitmap image.
struct FontCharacter
{
    Image mBitmap {};
    float mXOffset { 0 };
    float mYOffset { 0 };
    float mLeftSideBearing { 0 };
    float mGlyphWidth { 0 };
};

// Represents a string of characters in a specific font, including offsets for each character.
// And total width and height of the string.
struct FontString
{
    const std::vector<FontCharacter> mFontCharacters {};
    const float mWidth { 0 };
    const float mHeight { 0 };
};

class Font
{
public:
    Font() = default;
    ~Font() = default;

    std::string GetName() const;
    bool LoadFont(const std::string& fontName, const std::string& fontPath);
    FontString GetCharacters(const std::string& text);

private:
    FontCharacter LoadCharacter(const char character);
    FontCharacter GetCharacter(const char character);

    std::string mName {};
    std::unordered_map<char, FontCharacter> mCharacters {};
    std::vector<unsigned char> mFontData {};
    stbtt_fontinfo mFontInfo {};
    float mPixelScale { 0 };
    float mAscent { 0 };
    float mDescent { 0 };
    float mLineGap { 0 };
};

} // namespace pong
