#include "text.h"

#include "config.h"
#include "logger.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <fstream>

namespace pong
{

Text::Text()
{
    Text("Default", "D:/code/pong/assets/pixeloid.ttf", 1.0f, 128);
}

Text::Text(const std::string& text, const std::string& path, float scale, int pixelLineHeight) :
    mText { text },
    mFontPath { path },
    mScale { scale },
    mPixelLineHeight { pixelLineHeight }
{
    RecomputeText();
}

std::vector<OffsetGraphic> Text::GetRenderables()
{
    std::vector<OffsetGraphic> renderables {};
    const size_t totalRenderables = mCharacters.size();
    renderables.reserve(totalRenderables);
    for (auto& character : mCharacters)
    {
        renderables.emplace_back(character, character.mOffset);
    }
    return renderables;
}

BaseComponent* Text::GetBaseComponent()
{
    return this;
}

void Text::RecomputeText()
{
    std::ifstream file(mFontPath, std::ios::binary);
    if (!file)
    {
        RealTimeLogError("Failed to open true type font file: {}", mFontPath);
        ASSERT(false);
        return;
    }

    std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontData.data(), 0);

    const float pixelScale = stbtt_ScaleForPixelHeight(&font, static_cast<float>(mPixelLineHeight));

    float totalTextWidth = 0.0f;
    float totalTextHeight = 0.0f;
    float currentLineWidth = 0.0f;
    float currentLineHeight = 0.0f;

    int unscaledAscent, unscaledDescent, unscaledLineGap;
    stbtt_GetFontVMetrics(&font, &unscaledAscent, &unscaledDescent, &unscaledLineGap);

    const float ascent  = unscaledAscent  * pixelScale;
    const float descent = unscaledDescent * pixelScale;
    const float lineGap = unscaledLineGap * pixelScale;

    float currentX = 0;
    float currentY = 0;

    for (int i = 0; i < mText.length(); i++)
    {
        const char character = mText[i];

        int unscaledGlpyhWidth = 0;
	    int unscaledLeftSideBearing = 0;
        stbtt_GetCodepointHMetrics(&font, character, &unscaledGlpyhWidth, &unscaledLeftSideBearing);

        const float glpyhWidth = unscaledGlpyhWidth * pixelScale * mScale;
        const float leftSideBearing = unscaledLeftSideBearing * pixelScale * mScale;

        int xCoord1 = 0;
        int yCoord1 = 0;
        int xCoord2 = 0;
        int yCoord2 = 0;
        stbtt_GetCodepointBitmapBox(&font, character, pixelScale, pixelScale, &xCoord1, &yCoord1, &xCoord2, &yCoord2);

        const int charWidth  = xCoord2 - xCoord1;
        const int charHeight = yCoord2 - yCoord1;

        auto alphaTexture = std::vector<unsigned char>();
        alphaTexture.resize(charWidth * charHeight);

        if (character == '\n')
        {
            currentY -= (ascent - descent + lineGap) * mScale;
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
            const float characterYOffset = currentY - spaceAboveCharPixels * mScale;

            const float quadScreenWidth  = charWidth * mScale;
            const float quadScreenHeight = charHeight * mScale;

            const float lineHeight = fabs(characterYOffset - quadScreenHeight);
            if (lineHeight > currentLineHeight)
            {
                currentLineHeight = lineHeight;
            }
            currentLineWidth = quadScreenWidth;

            // Since this uses a single character for each texture, stride is just the pixel width of the character
            const int kStride = charWidth;
            stbtt_MakeCodepointBitmap(&font, alphaTexture.data(), charWidth, charHeight, kStride, pixelScale, pixelScale, character);

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

            // TODO: Needs to also be checked after a \n character
            if (i == mText.length() - 1)
            {
                currentX -= glpyhWidth - quadScreenWidth;
            }
        }

        const int kern = stbtt_GetCodepointKernAdvance(&font, character, mText[i + 1]);
        currentX += fabs(kern * mScale * pixelScale);
        currentLineWidth = currentX;
    }

    if (currentLineWidth > totalTextWidth)
    {
        totalTextWidth = currentLineWidth;
    }
    totalTextHeight += currentLineHeight;

    // Characters have been created with their top left corner at the origin, so offset them to the center
    const glm::vec3 center = glm::vec3(totalTextWidth / 2.0f, -totalTextHeight / 2.0f, 0.0f);
    for (auto& character : mCharacters)
    {
        const glm::vec3 currentOffset = character.mOffset;
        character.mOffset = currentOffset - center;
        character.SetColor(mColor);
    }
}

std::string Text::GetText() const
{
    return mText;
}

void Text::SetText(const std::string& text)
{
    mText = text;
    mCharacters.clear();
    RecomputeText();
}

void Text::SetScale(float scale)
{
    mScale = scale;
    mCharacters.clear();
    RecomputeText();
}

void Text::SetPixelLineHeight(int pixelLineHeight)
{
    mPixelLineHeight = pixelLineHeight;
    mCharacters.clear();
    RecomputeText();
}

void Text::SetColor(GLRGBAColor color)
{
    mColor = color;
    for (auto& character : mCharacters)
    {
        character.SetColor(mColor);
    }
}

} // namespace pong
