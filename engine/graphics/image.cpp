#include "image.h"

#include "utils.h"

namespace pong
{

namespace image
{

/* Converts an alpha image to RGBA format. */
std::vector<unsigned char> ConvertAlphaImageToRGBA(const std::vector<unsigned char>& imageData)
{
    std::vector<unsigned char> convertedImage {};
    convertedImage.reserve(imageData.size() * 4);

    const unsigned char kFullColor = 255;
    for (auto& alpha : imageData)
    {
        convertedImage.emplace_back(kFullColor);
        convertedImage.emplace_back(kFullColor);
        convertedImage.emplace_back(kFullColor);
        convertedImage.emplace_back(alpha);
    }

    return convertedImage;
}

/* Flips an image so top left element becomes bottom left element. */
std::vector<unsigned char> FlipImageVertically(const std::vector<unsigned char>& imageData, int width, int height, int comp)
{
    ASSERT(imageData.size() == width * height * comp);

    std::vector<unsigned char> flippedImage {};
    flippedImage.reserve(imageData.size());

    const int stride = width * comp;
    for (int rowNumber = height - 1; rowNumber >= 0; rowNumber--)
    {
        const int rowIndex = rowNumber * stride;
        for (int colNumber = 0; colNumber < width; colNumber++)
        {
            // For each pixel, copy all the components
            const int pixelIndex = rowIndex + (colNumber * comp);
            for (int componentIndex = 0; componentIndex < comp; componentIndex++)
            {
                flippedImage.emplace_back(imageData[pixelIndex + componentIndex]);
            }
        }
    }

    return flippedImage;
}

} // namespace image
} // namespace pong
