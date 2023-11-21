#include "text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma warning(push, 0)
#include <stb_image_write.h>
#pragma warning(pop)

#include <fstream>
#include <iostream>


namespace pong
{

Text::Text(const std::string&, const std::string& path, int size)
{
    (void)size;

    // read file contents located at path
    std::ifstream stream(path);

    /* Simplest example of rendering entire font to bitmap image
    unsigned char ttf_buffer[100000];
    #pragma warning(suppress: 4996)
    fread(ttf_buffer, 1, 100000, fopen(path.c_str(), "rb"));
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    stbtt_BakeFontBitmap(ttf_buffer, 0, static_cast<float>(size), mPixels, 512, 512, 32, 96, cdata);
    */

    unsigned char ttf_buffer[100000];
    #pragma warning(suppress: 4996)
    fread(ttf_buffer, 1, 100000, fopen(path.c_str(), "rb"));


    const char* text = "Heljo World!";
    stbtt_fontinfo font;
    stbtt_InitFont(&font, ttf_buffer, 0);

    std::cout << "Space ascii value: " << static_cast<int>(' ') << std::endl;

    const char character = text[1];
    const int stride = 64;
    float scale = stbtt_ScaleForPixelHeight(&font, stride);

    int c_x1, c_y1, c_x2, c_y2;
    stbtt_GetCodepointBitmapBox(&font, character, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
    const int width = c_x2 - c_x1;
    const int height = c_y2 - c_y1;

    std::cout << "coords: " << c_x1 << ", " << c_x2 << ", " << c_y1 << ", " << c_y2 << std::endl;

    unsigned char mPixels[512 * 512];

    stbtt_MakeCodepointBitmap(&font, mPixels, width, height, stride, scale, scale, character);



    stbi_write_png("image.png", width, height, 1, mPixels, stride);
}

} // namespace pong
