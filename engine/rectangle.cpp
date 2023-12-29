#include "rectangle.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <array>
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
    RecomputeVertices();
    mTexture = Texture(RGBA_WHITE);
}

void Rectangle::RecomputeVertices()
{
    const std::array<float, 16> positions = {
        -mWidth / 2.0f, -mHeight / 2.0f, 0.0f, 0.0f,
         mWidth / 2.0f, -mHeight / 2.0f, 1.0f, 0.0f,
         mWidth / 2.0f,  mHeight / 2.0f, 1.0f, 1.0f,
        -mWidth / 2.0f,  mHeight / 2.0f, 0.0f, 1.0f
    };

    mVB = VertexBuffer(positions.data(), static_cast<unsigned int>(positions.size() * sizeof(float)));
    mIB = IndexBuffer(kIndicies.data(), static_cast<unsigned int>(kIndicies.size()));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVA.AddBuffer(mVB, layout);
}

float Rectangle::GetWidth() const
{
    return mWidth;
}

float Rectangle::GetHeight() const
{
    return mHeight;
}

void Rectangle::Resize(float width, float height)
{
    mWidth = width;
    mHeight = height;

    RecomputeVertices();
}

} // namespace pong
