#pragma once

#include <stb_truetype.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace pong
{

struct FontCharacter
{
    std::vector<unsigned char> mBitmap {};
    int mBitmapWidth { 0 };
    int mBitmapHeight { 0 };
    float mXOffset { 0 };
    float mYOffset { 0 };
    float mLeftSideBearing { 0 };
    float mGlyphWidth { 0 };
};

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

    bool LoadFont(const std::string& fontName, const std::string& fontPath);
    FontString GetCharacters(const std::string& text);

private:
    FontCharacter LoadCharacter(const char character);
    FontCharacter GetCharacter(const char character);

    std::unordered_map<char, FontCharacter> mCharacters {};
    std::vector<unsigned char> mFontData {};
    stbtt_fontinfo* mFontInfo { nullptr };
    float mPixelScale { 0 };
    float mAscent { 0 };
    float mDescent { 0 };
    float mLineGap { 0 };

};

} // namespace pong
