#pragma once

#include "renderer.h"

class Texture
{
private:
    std::string mFilePath {""};
    unsigned char* mLocalBuffer { nullptr };
protected:
    int mWidth {0};
    int mHeight {0};
    int mBPP {0};
    unsigned int mRendererID {0};
public:
    Texture() = default;
    explicit Texture(const std::string& filePath);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;

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
