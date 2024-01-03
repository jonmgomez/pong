#include "text.h"

#include "config.h"
#include "font.h"
#include "logger.h"
#include "pong.h"

#include <fstream>

namespace pong
{

Text::Text(const std::string& text, Font* font, float scale) :
    mText { text },
    mFont { font },
    mScale { scale }
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
    ASSERT(mFont != nullptr);

    const FontString fontString = mFont->GetCharacters(mText);
    const std::vector<FontCharacter>& fontCharacters = fontString.mFontCharacters;

    for (const FontCharacter& character : fontCharacters)
    {
        const float quadWidth = character.mBitmap.mWidth * mScale;
        const float quadHeight = character.mBitmap.mHeight * mScale;
        const float xOffset = character.mXOffset * mScale;
        const float yOffset = character.mYOffset * mScale;
        mCharacters.emplace_back(character.mBitmap, glm::vec3(xOffset, -yOffset, 0.0f),
                                 quadWidth, quadHeight);
    }

    const float totalTextWidth = fontString.mWidth * mScale;
    const float totalTextHeight = fontString.mHeight * mScale;

    // Characters have been created with their top left corner at the origin,
    // so offset them to the center of the whole text
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

void Text::SetFont(Font* font)
{
    mFont = font;
    mCharacters.clear();
    RecomputeText();
}

void Text::SetScale(float scale)
{
    mScale = scale;
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
