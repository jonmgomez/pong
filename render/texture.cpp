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

Texture Texture::CreateFromFile(const std::string& filePath)
{
    stbi_set_flip_vertically_on_load(1);

    int bytesPerPixel = 0;
    int width = 0;
    int height = 0;
    unsigned char* buffer = stbi_load(filePath.c_str(), &width, &height, &bytesPerPixel, 4);

    Texture texture(*buffer, width, height, GL_RGBA);

    if (buffer)
    {
        stbi_image_free(buffer);
    }

    return std::move(texture);
}

Texture Texture::CreateFromFontCharacter(const std::vector<unsigned char>& imageData, int width, int height)
{
    auto rgbTexture = Texture::ConvertAlphaImageToRGBA(imageData);
    std::vector<unsigned char> flippedImageData {};
    FlipImageVertically(rgbTexture, width, height, 4, flippedImageData);

    return Texture(*flippedImageData.data(), width, height, GL_RGBA);
}

Texture Texture::CreateFromSolidColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char data[] = { r, g, b, a };
    constexpr int kWidth = 1;
    constexpr int kHeight = 1;

    return Texture(*data, kWidth, kHeight, GL_RGBA);
}

Texture::Texture(const unsigned char& imageData, int width, int height, GLenum format) :
    mWidth(width),
    mHeight(height)
{
    GLCall(glGenTextures(1, &mRendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

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
    mRendererID(other.mRendererID)
{
    other.mRendererID = 0;
    other.mWidth = 0;
    other.mHeight = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    if (this != &other)
    {
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mRendererID = other.mRendererID;
        other.mWidth = 0;
        other.mHeight = 0;
        other.mRendererID = 0;
    }

    return *this;
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

void Texture::FlipImageVertically(const std::vector<unsigned char>& imageData, int width, int height, int comp, std::vector<unsigned char>& outFlippedImageData)
{
    ASSERT(imageData.size() == width * height * comp);

    outFlippedImageData.reserve(imageData.size());
    for (int rowIndex = height - 1; rowIndex >= 0; rowIndex--)
    {
        for (int colIndex = 0; colIndex < width; colIndex++)
        {
            // For each pixel, copy all the components
            const int index = (rowIndex * width * comp) + (colIndex * comp);
            for (int formatIndex = 0; formatIndex < comp; formatIndex++)
            {
                outFlippedImageData.emplace_back(imageData[index + formatIndex]);
            }
        }
    }
}

} // namespace pong
