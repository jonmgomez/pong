#include "font.h"

#include "image.h"
#include "logger.h"
#include "utils.h"

#ifndef STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#endif

#include <fstream>

namespace pong
{

// The font will load these characters by default.
// If a character is not in this list, it will be loaded the first time it is used.
static constexpr std::string_view DEFAULT_FONT_CHARACTERS =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=_+[]{}\\|;:'\",<.>/?`~ ";

static constexpr int PIXEL_LINE_HEIGHT = 256;

bool Font::LoadFont(const std::string& fontName, const std::string& fontPath)
{
    std::ifstream file(fontPath, std::ios::binary);
    if (!file)
    {
        LogError("Failed to open true type font file: {} - {}", fontPath, fontName);
        ASSERT(false);
        return false;
    }

    mFontData = std::vector<unsigned char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ASSERT(stbtt_InitFont(&mFontInfo, mFontData.data(), 0) != 0);

    mPixelScale = stbtt_ScaleForPixelHeight(&mFontInfo, static_cast<float>(PIXEL_LINE_HEIGHT));

    int unscaledAscent, unscaledDescent, unscaledLineGap;
    stbtt_GetFontVMetrics(&mFontInfo, &unscaledAscent, &unscaledDescent, &unscaledLineGap);

    mAscent  = unscaledAscent  * mPixelScale;
    mDescent = unscaledDescent * mPixelScale;
    mLineGap = unscaledLineGap * mPixelScale;

    for (const char& character : DEFAULT_FONT_CHARACTERS)
    {
        LoadCharacter(character);
    }

    return true;
}

FontCharacter Font::LoadCharacter(const char character)
{
    FontCharacter fontCharacter {};

    int unscaledGlpyhWidth = 0;
    int unscaledLeftSideBearing = 0;
    stbtt_GetCodepointHMetrics(&mFontInfo, character, &unscaledGlpyhWidth, &unscaledLeftSideBearing);

    fontCharacter.mGlyphWidth = unscaledGlpyhWidth * mPixelScale;
    fontCharacter.mLeftSideBearing = unscaledLeftSideBearing * mPixelScale;

    int xCoord1 = 0;
    int yCoord1 = 0;
    int xCoord2 = 0;
    int yCoord2 = 0;
    stbtt_GetCodepointBitmapBox(&mFontInfo, character, mPixelScale, mPixelScale,
                                &xCoord1, &yCoord1, &xCoord2, &yCoord2);

    const int charWidth  = xCoord2 - xCoord1;
    const int charHeight = yCoord2 - yCoord1;

    const float spaceAboveCharPixels = mAscent + yCoord1;
    fontCharacter.mYOffset = spaceAboveCharPixels;

    fontCharacter.mBitmap.mPixels.resize(charWidth * charHeight);

    if (character != '\n')
    {
        // Since this uses a single character for each texture, stride is just the pixel width of the character
        const int kStride = charWidth;
        stbtt_MakeCodepointBitmap(&mFontInfo, fontCharacter.mBitmap.mPixels.data(),
                                  charWidth, charHeight, kStride,
                                  mPixelScale, mPixelScale,
                                  character);

        fontCharacter.mBitmap.mWidth = charWidth;
        fontCharacter.mBitmap.mHeight = charHeight;
        fontCharacter.mBitmap.mComponents = 1;
    }

    // Bitmap returned is alpha only, and stored bottom left pixel first
    // Convert to RGBA and flip it for OpenGL
    const auto rgbTexture = image::ConvertAlphaImageToRGBA(fontCharacter.mBitmap);
    fontCharacter.mBitmap = image::FlipImageVertically(rgbTexture);

    mCharacters[character] = fontCharacter;
    return fontCharacter;
}

FontString Font::GetCharacters(const std::string& text)
{
    std::vector<FontCharacter> fontCharacters {};

    float totalTextWidth = 0.0f;
    float totalTextHeight = 0.0f;
    float currentLineHeight = 0.0f;
    float currentX = 0.0f;
    float currentY = 0.0f;

    stbtt_InitFont(&mFontInfo, mFontData.data(), 0);

    for (int i = 0; i < text.length(); i++)
    {
        const char character = text[i];
        FontCharacter fontCharacter = GetCharacter(character);

        if (character == '\n')
        {
            currentX = 0;
            currentY += (mAscent - mDescent + mLineGap);
        }
        else
        {
            currentLineHeight = std::fabs(fontCharacter.mYOffset + fontCharacter.mBitmap.mHeight);

            // Left side bearing is the amount of space between the previous character and this one
            // The first character does not need to take this into account
            if (i > 0)
            {
                currentX += fontCharacter.mLeftSideBearing;
            }

            fontCharacter.mYOffset += currentY;
            // Offset the character to the center of the quad
            fontCharacter.mXOffset = currentX + fontCharacter.mBitmap.mWidth / 2.0f;
            fontCharacter.mYOffset += fontCharacter.mBitmap.mHeight / 2.0f;

            currentX += fontCharacter.mGlyphWidth;
        }

        totalTextWidth = std::max(totalTextWidth, currentX);
        totalTextHeight = std::max(totalTextHeight, currentY + currentLineHeight);

        if (i < text.length() - 1)
        {
            // The kerning is the amount of space between a specific character pair
            // This can only be calculated if the next character is known
            const int kern = stbtt_GetCodepointKernAdvance(&mFontInfo, character, text[i + 1]);
            currentX += std::fabs(kern * mPixelScale);
        }

        fontCharacters.push_back(fontCharacter);
    }

    return { fontCharacters, totalTextWidth, totalTextHeight };
}

// Gets the font character from the cache, or loads it if it doesn't exist
FontCharacter Font::GetCharacter(const char character)
{
    auto it = mCharacters.find(character);
    if (it == mCharacters.end())
    {
        LogDebug("Character {} not found in cache, loading it", character);
        return LoadCharacter(character);
    }

    return it->second;
}

} // namespace pong
