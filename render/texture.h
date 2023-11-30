#pragma once

#include "renderutils.h"

#include <GL/glew.h>

#include <string>
#include <vector>

namespace pong
{

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& filePath);
    Texture(const RGBAColor& color);
    /* Assumes the data is grayscale and stored from top left to bottom right in vector */
    Texture(const std::vector<unsigned char>& alphaImage, int width, int height);
    Texture(const unsigned char& imageData, int width, int height, GLenum format);

    // Copy constructors are deleted because the renderer id is used to destroy the object in opengl
    // in the destructor. The move operator gets around this by setting the renderer id to 0.
    // The same goes for other opengl objects.
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&);
    Texture& operator=(Texture&&);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetWidth() const;
    int GetHeight() const;

    static std::vector<unsigned char> ConvertAlphaImageToRGBA(const std::vector<unsigned char>& imageData);
    static std::vector<unsigned char> FlipImageVertically(const std::vector<unsigned char>& imageData, int width, int height, int comp);

protected:
    int mWidth {0};
    int mHeight {0};
    unsigned int mRendererID {0};

private:
    std::string mFilePath {""};
};

} // namespace pong
