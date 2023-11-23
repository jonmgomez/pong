#pragma once

#include <string>
#include <vector>

namespace pong
{

class Texture
{
public:
    Texture() = default;
    explicit Texture(const std::string& filePath);
    explicit Texture(const std::vector<unsigned char>& imageData, int width, int height);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetWidth() const;
    int GetHeight() const;

    static std::vector<unsigned char> ConvertAlphaImageToRGBA(const std::vector<unsigned char>& imageData);
    static void FlipImageVertically(const std::vector<unsigned char>& imageData, int width, int height, int comp, std::vector<unsigned char>& outFlippedImageData);

protected:
    int mWidth {0};
    int mHeight {0};
    unsigned int mRendererID {0};

private:
    std::string mFilePath {""};
};

class SolidColorTexture : public Texture
{
public:
    SolidColorTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    ~SolidColorTexture();
};

} // namespace pong
