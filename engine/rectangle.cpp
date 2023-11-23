#include "rectangle.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace pong
{

static const std::array<unsigned int, 6> kIndicies = {
    0, 1, 2,
    2, 3, 0
};

Rectangle::Rectangle(float width, float height) :
    mWidth {width},
    mHeight {height}
{
    CreateQuad(width, height);

    const unsigned char kColorValue = 255;
    mTexture = Texture::CreateFromSolidColor(kColorValue, kColorValue, kColorValue, kColorValue);
}

void Rectangle::CreateQuad(float width, float height)
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
}

} // namespace pong
