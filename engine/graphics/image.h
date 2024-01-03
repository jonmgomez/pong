#pragma once

#include <vector>

namespace pong::image
{

struct Image
{
    std::vector<unsigned char> mPixels {};
    int mWidth { 0 };
    int mHeight { 0 };
    int mComponents { 0 };
};


Image ConvertAlphaImageToRGBA(const Image& image);
Image FlipImageVertically(const Image& image);

} // namespace pong::image
