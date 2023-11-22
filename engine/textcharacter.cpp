#include "textcharacter.h"

#include <array>

namespace pong
{

static const std::array<unsigned int, 6> kIndicies = {
    0, 1, 2,
    2, 3, 0
};

TextCharacter::TextCharacter(const std::vector<unsigned char>& data, float width, float height, const glm::vec3& offset, int textureWidth, int textureHeight) :
    mOffset(offset)
{
    const std::array<float, 16> positions = {
        -width / 2, -height / 2, 0.0f, 0.0f,
         width / 2, -height / 2, 1.0f, 0.0f,
         width / 2,  height / 2, 1.0f, 1.0f,
        -width / 2,  height / 2, 0.0f, 1.0f
    };

    mVB = VertexBuffer(positions.data(), static_cast<unsigned int>(positions.size() * sizeof(float)));
    mIB = IndexBuffer(kIndicies.data(), static_cast<unsigned int>(kIndicies.size()));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVA.AddBuffer(mVB, layout);

    std::cout << "Texture width: " << textureWidth << ", height: " << textureHeight << std::endl;
    std::cout << "Offset x: " << offset.x << ", y: " << offset.y << std::endl;
    mTexture = std::make_unique<Texture>(data, textureWidth, textureHeight);
}

void TextCharacter::Draw(const glm::vec3& position) const
{
    Mesh::Draw(position + mOffset);
}

} // namespace pong
