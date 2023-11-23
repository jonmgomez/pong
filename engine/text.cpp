#include "text.h"

#include "pong.h"
#include "wall.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma warning(push, 0)
#include <stb_image_write.h>
#pragma warning(pop)

#include <fstream>
#include <iostream>
#include <sstream>


namespace pong
{

Text::Text(const std::string& text, const std::string& path, float size, int pixelLineHeight) :
    mText { text },
    mFontPath { path },
    mSize { size },
    mPixelLineHeight { pixelLineHeight }
{
    CreateText();
}

void Text::CreateText()
{
    std::ifstream file(mFontPath, std::ios::binary);
    if (!file)
    {
        std::cout << "Failed to open file: " << mFontPath << std::endl;
        return;
    }

    std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontData.data(), 0);

    const float scale = stbtt_ScaleForPixelHeight(&font, static_cast<float>(mPixelLineHeight));

    float totalTextWidth = 0.0f;
    float totalTextHeight = 0.0f;
    float currentLineWidth = 0.0f;
    float currentLineHeight = 0.0f;

    int unscaledAscent, unscaledDescent, unscaledLineGap;
    stbtt_GetFontVMetrics(&font, &unscaledAscent, &unscaledDescent, &unscaledLineGap);

    const float ascent  = unscaledAscent  * scale;
    const float descent = unscaledDescent * scale;
    const float lineGap = unscaledLineGap * scale;

    float currentX = 0;
    float currentY = 0;

    for (int i = 0; i < mText.length(); i++)
    {
        const char character = mText[i];

        int unscaledGlpyhWidth = 0;
	    int unscaledLeftSideBearing = 0;
        stbtt_GetCodepointHMetrics(&font, character, &unscaledGlpyhWidth, &unscaledLeftSideBearing);

        const float glpyhWidth = unscaledGlpyhWidth * scale;
        const float leftSideBearing = unscaledLeftSideBearing * scale;
        std::cout << character << ": glpyhWidth: " << glpyhWidth << ", leftSideBearing: " << leftSideBearing << std::endl;

        int xCoord1 = 0;
        int yCoord1 = 0;
        int xCoord2 = 0;
        int yCoord2 = 0;
        stbtt_GetCodepointBitmapBox(&font, character, scale, scale, &xCoord1, &yCoord1, &xCoord2, &yCoord2);
        std::cout << character << ": x1: " << xCoord1 << ", y1: " << yCoord1 << ", x2: " << xCoord2 << ", y2: " << yCoord2 << std::endl;

        const int charWidth  = xCoord2 - xCoord1;
        const int charHeight = yCoord2 - yCoord1;

        auto alphaTexture = std::vector<unsigned char>();
        alphaTexture.resize(charWidth * charHeight);

        if (character == '\n')
        {
            currentY -= (ascent - descent + lineGap) * mSize;
            currentX = 0;

            if (currentLineWidth > totalTextWidth)
            {
                totalTextWidth = currentLineWidth;
            }
            totalTextHeight = fabs(currentY);
            currentLineWidth = 0;
            currentLineHeight = 0;
        }
        else
        {
            const float spaceAboveCharPixels = ascent + yCoord1;
            const float characterYOffset = currentY - spaceAboveCharPixels * mSize;

            const float quadScreenWidth  = charWidth * mSize;
            const float quadScreenHeight = charHeight * mSize;

            std::cout << character << ": " << quadScreenWidth << ", " << quadScreenHeight << std::endl;

            const float lineHeight = fabs(characterYOffset - quadScreenHeight);
            if (lineHeight > currentLineHeight)
            {
                currentLineHeight = lineHeight;
            }
            currentLineWidth = quadScreenWidth;

            // Since this uses a single character for each texture, stride is just the pixel width of the character
            const int kStride = charWidth;
            stbtt_MakeCodepointBitmap(&font, alphaTexture.data(), charWidth, charHeight, kStride, scale, scale, character);

            if (i > 0)
            {
                currentX += leftSideBearing;
            }

            // Since the current offset is the top left, offset it to center of quad
            const float finalXOffset = currentX + quadScreenWidth / 2.0f;
            const float finalYOffset = characterYOffset - quadScreenHeight / 2.0f;

            mCharacters.emplace_back(alphaTexture, quadScreenWidth, quadScreenHeight,
                                     glm::vec3(finalXOffset, finalYOffset, 0.0f),
                                     charWidth, charHeight);

            currentX += glpyhWidth;

            // Needs to also be checked after a \n character
            if (i == mText.length() - 1)
            {
                currentX -= glpyhWidth - quadScreenWidth;
            }
        }

        const int kern = stbtt_GetCodepointKernAdvance(&font, character, mText[i + 1]);
        currentX += fabs(kern * mSize * scale);
        currentLineWidth = currentX;
    }

    if (currentLineWidth > totalTextWidth)
    {
        totalTextWidth = currentLineWidth;
    }
    totalTextHeight += currentLineHeight;

    std::cout << "Total width: " << totalTextWidth << ", Total height: " << totalTextHeight << std::endl;

    // Characters have been created with their top left corner at the origin, so offset them to the center
    const glm::vec3 center = glm::vec3(totalTextWidth / 2.0f, -totalTextHeight / 2.0f, 0.0f);


    for (auto& character : mCharacters)
    {
        const glm::vec3 currentOffset = character.GetOffset();
        character.SetOffset(currentOffset - center);
    }
}

glm::vec3 Text::GetPosition() const
{
    return mPosition;
}

void Text::SetPosition(const glm::vec3& position)
{
    mPosition = position;
}

void Text::SetText(const std::string& text)
{
    mText = text;
    mCharacters.clear();
    CreateText();
}

void Text::Render()
{
    for (const auto& character : mCharacters)
    {
        character.Draw(mPosition);
    }
}

} // namespace pong
