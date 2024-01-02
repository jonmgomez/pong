#include "texture.h"

#include "image.h"
#include "renderutils.h"

// Ignore numerous warnings from stb_image.h
#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#pragma warning(pop)

#include <array>
#include <iostream>

namespace pong
{

Texture::Texture(const std::string& filePath)
{
    stbi_set_flip_vertically_on_load(1);

    int bytesPerPixel = 0;
    int width = 0;
    int height = 0;
    unsigned char* buffer = stbi_load(filePath.c_str(), &width, &height, &bytesPerPixel, 4);

    this->Texture::Texture(*buffer, width, height, GL_RGBA);

    if (buffer)
    {
        stbi_image_free(buffer);
    }
}

Texture::Texture(const std::vector<unsigned char>& alphaImage, int width, int height)
{
    // auto rgbTexture = image::ConvertAlphaImageToRGBA(alphaImage);
    // auto finalImage = image::FlipImageVertically(rgbTexture, width, height, 4);

    this->Texture::Texture(*alphaImage.data(), width, height, GL_RGBA);
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
