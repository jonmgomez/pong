#include "textcharacter.h"

#include <array>

namespace pong
{

static const std::array<unsigned int, 6> kIndicies = {
    0, 1, 2,
    2, 3, 0
};

TextCharacter::TextCharacter(const Image& image, const glm::vec3& offset,
                             float width, float height) :
    Rectangle(width, height),
    mOffset(offset)
{
    mTexture = Texture(image.mPixels, image.mWidth, image.mHeight);
}

} // namespace pong
