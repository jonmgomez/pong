#include "textcharacter.h"

#include <array>

namespace pong
{

static const std::array<unsigned int, 6> kIndicies = {
    0, 1, 2,
    2, 3, 0
};

TextCharacter::TextCharacter(const std::vector<unsigned char>& data,
                            float width, float height, const glm::vec3& offset,
                            int textureWidthPixels, int textureHeightPixels) :
    Rectangle(width, height),
    mOffset(offset)
{
    mTexture = Texture(data, textureWidthPixels, textureHeightPixels);
}

} // namespace pong
