#pragma once

#include <vector>

namespace pong
{

namespace image
{

std::vector<unsigned char> ConvertAlphaImageToRGBA(const std::vector<unsigned char>& imageData);
std::vector<unsigned char> FlipImageVertically(const std::vector<unsigned char>& imageData, int width, int height, int comp);

} // namespace image
} // namespace pong
