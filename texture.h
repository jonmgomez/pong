#pragma once

#include "renderer.h"

class Texture
{
private:
    std::string mFilePath;
    unsigned char* mLocalBuffer;
    int mWidth, mHeight, mBPP;
protected:
    unsigned int mRendererID;
public:
    Texture(const std::string& filePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetWidth() const;
    int GetHeight() const;
};

class SolidColorTexture : public Texture
{
public:
    SolidColorTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    ~SolidColorTexture();
};
