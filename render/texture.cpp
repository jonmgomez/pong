#include "texture.h"

#include "image.h"
#include "renderutils.h"

#include <array>
#include <iostream>

namespace pong
{

using image::Image;

Texture::Texture(const std::string& filePath)
{
    const bool kFlipVertically = true;
    Image image = image::LoadImage(filePath, kFlipVertically);
    this->Texture::Texture(*image.mPixels.data(), image.mWidth, image.mHeight, GL_RGBA);
}

Texture::Texture(const std::vector<unsigned char>& rgbaImage, int width, int height)
{
    this->Texture::Texture(*rgbaImage.data(), width, height, GL_RGBA);
}

Texture::Texture(const RGBAColor& color)
{
    const std::array<unsigned char, 4> pixel { color.r, color.g, color.b, color.a };
    constexpr int kWidth = 1;
    constexpr int kHeight = 1;

    this->Texture::Texture(*pixel.data(), kWidth, kHeight, GL_RGBA);
}

Texture::Texture(const unsigned char& imageData, int width, int height, GLenum format) :
    mWidth(width),
    mHeight(height)
{
    GLCall(glGenTextures(1, &mRendererId));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, &imageData));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(Texture&& other) :
    mWidth(other.mWidth),
    mHeight(other.mHeight),
    mRendererId(other.mRendererId)
{
    other.mRendererId = 0;
    other.mWidth = 0;
    other.mHeight = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    if (this != &other)
    {
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mRendererId = other.mRendererId;
        other.mWidth = 0;
        other.mHeight = 0;
        other.mRendererId = 0;
    }

    return *this;
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &mRendererId));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererId));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::GetHeight() const
{
    return mHeight;
}

int Texture::GetWidth() const
{
    return mWidth;
}

} // namespace pong
