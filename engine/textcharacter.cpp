#include "textcharacter.h"

#include <array>

namespace pong
{

static const std::array<unsigned int, 6> kIndicies = {
    0, 1, 2,
    2, 3, 0
};

TextCharacter::TextCharacter(const std::vector<unsigned char>& data, float width, float height, const glm::vec3& offset, int textureWidth, int textureHeight) :
    Rectangle(width, height),
    mOffset(offset)
{
    mTexture = Texture::CreateFromFontCharacter(data, textureWidth, textureHeight);
}

void TextCharacter::Draw(const glm::vec3& position) const
{
    Mesh::Draw(position + mOffset);
}

} // namespace pong
