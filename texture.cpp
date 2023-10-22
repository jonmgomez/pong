#include "texture.h"

#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

#include <iostream>

#include "renderutils.h"

Texture::Texture(const std::string& filePath)
    : mRendererID(0), mFilePath(filePath), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mBPP, 4);

    GLCall(glGenTextures(1, &mRendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    // for (int i = 0; i < mWidth * mHeight; i+=4)
    // {
    //     std::cout << "(" << (int)mLocalBuffer[i] << "," << (int)mLocalBuffer[i + 1] << "," << (int)mLocalBuffer[i + 2] << "," << (int)mLocalBuffer[i + 3] << ")" << "\n";
    // }

    // std::cout << "size: " << mWidth * mHeight << std::endl;

    if (mLocalBuffer)
    {
        stbi_image_free(mLocalBuffer);
    }
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



SolidColorTexture::SolidColorTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : Texture("")
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
