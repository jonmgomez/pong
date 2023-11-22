#include "texture.h"

#include "renderutils.h"

// Ignore numerous warnings from stb_image.h
#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

#include <iostream>

namespace pong
{

Texture::Texture(const std::string& filePath)
{
    stbi_set_flip_vertically_on_load(1);

    int bpp = 0;
    unsigned char* buffer = stbi_load(filePath.c_str(), &mWidth, &mHeight, &bpp, 4);

    GLCall(glGenTextures(1, &mRendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (buffer)
    {
        stbi_image_free(buffer);
    }
}

Texture::Texture(const std::vector<unsigned char>& imageData, int width, int height) :
    mWidth(width),
    mHeight(height)
{
    GLCall(glGenTextures(1, &mRendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data()));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &mRendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));
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

/* Converts a grayscale image to RGBA format */
std::vector<unsigned char> Texture::ConvertAlphaImageToRGBA(const std::vector<unsigned char>& imageData)
{
    std::vector<unsigned char> convertedImage {};
    convertedImage.reserve(imageData.size() * 4);

    for (auto& alpha : imageData)
    {
        convertedImage.push_back(255);
        convertedImage.push_back(255);
        convertedImage.push_back(255);
        convertedImage.push_back(alpha);
    }

    return std::move(convertedImage);
}


SolidColorTexture::SolidColorTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char data[] = { r, g, b, a };
    GLCall(glGenTextures(1, &mRendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

SolidColorTexture::~SolidColorTexture()
{
    GLCall(glDeleteTextures(1, &mRendererID));
}

} // namespace pong
