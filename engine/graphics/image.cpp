#include "image.h"

#include "utils.h"

namespace pong::image
{

/* Converts an alpha image to RGBA format. */
Image ConvertAlphaImageToRGBA(const Image& image)
{
    ASSERT(image.mComponents == 1);

    Image convertedImage {};
    convertedImage.mPixels.reserve(image.mPixels.size() * 4);

    const unsigned char kFullColor = 255;
    for (auto& alpha : image.mPixels)
    {
        convertedImage.mPixels.push_back(kFullColor);
        convertedImage.mPixels.push_back(kFullColor);
        convertedImage.mPixels.push_back(kFullColor);
        convertedImage.mPixels.push_back(alpha);
    }

    convertedImage.mWidth = image.mWidth;
    convertedImage.mHeight = image.mHeight;
    convertedImage.mComponents = 4;

    return convertedImage;
}

/* Flips an image so top left element becomes bottom left element. */
Image FlipImageVertically(const Image& image)
{
    const std::vector<unsigned char>& pixels = image.mPixels;
    ASSERT(pixels.size() == image.mWidth * image.mHeight * image.mComponents);

    Image flippedImage {};
    flippedImage.mPixels.reserve(pixels.size());

    const int stride = image.mWidth * image.mComponents;
    for (int rowNumber = image.mHeight - 1; rowNumber >= 0; rowNumber--)
    {
        const int rowIndex = rowNumber * stride;
        for (int colNumber = 0; colNumber < image.mWidth; colNumber++)
        {
            // For each pixel, copy all the components
            const int pixelIndex = rowIndex + (colNumber * image.mComponents);
            for (int componentIndex = 0; componentIndex < image.mComponents; componentIndex++)
            {
                flippedImage.mPixels.push_back(pixels[pixelIndex + componentIndex]);
            }
        }
    }

    flippedImage.mWidth = image.mWidth;
    flippedImage.mHeight = image.mHeight;
    flippedImage.mComponents = image.mComponents;

    return flippedImage;
}

} // namespace pong::image
