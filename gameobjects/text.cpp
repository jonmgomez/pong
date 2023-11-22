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

Text::Text(const std::string& text, const std::string& path, int size)
{
    (void)text;
    (void)size;

    std::ifstream stream(path);
    if (!stream.is_open())
    {
        std::cout << "Failed to open file: " << path << std::endl;
        return;
    }

    // const float BASE_SCREEN_WIDTH = 1024.0f;
    // const float BASE_SCREEN_HEIGHT = 768.0f;

    // std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    // stbtt_fontinfo font;
    // stbtt_InitFont(&font, fontData.data(), 0);

    // const int lineHeight = 64; // In pixels
    // const float scale = stbtt_ScaleForPixelHeight(&font, lineHeight);

    // float currentX = 0;
    // float currentY = 0;
    // int unscaledAscent, unscaledDescent, lineGap;
    // stbtt_GetFontVMetrics(&font, &unscaledAscent, &unscaledDescent, &lineGap);

    // const float ascent = unscaledAscent * scale;
    // const float descent = unscaledDescent * scale;

    // for (int i = 0; i < text.length(); ++i)
    // {
    //     // b_w IS EQUIVALENT TO SCREEN WIDTH
    //     const char character = text[i];

    //     int glpyhWidth = 0;
	//     int leftSideBearing = 0;
    //     stbtt_GetCodepointHMetrics(&font, character, &glpyhWidth, &leftSideBearing);

    //     int xCoord1, yCoord1, xCoord2, yCoord2;
    //     stbtt_GetCodepointBitmapBox(&font, character, scale, scale, &xCoord1, &yCoord1, &xCoord2, &yCoord2);

    //     const int charWidth = xCoord2 - xCoord1;
    //     const int charHeight = yCoord2 - yCoord1;

    //     auto texture = std::make_unique<unsigned char[]>(charWidth * charHeight);

    //     if (character == '\n')
    //     {
    //         // SAVE
    //         currentY += (ascent - descent + lineGap) * scale;
    //         std::cout << "New Y: " << currentY << std::endl;
    //     }
    //     else
    //     {
    //         // Save this to some variable for the character
    //         // Or just use it in positioning
    //         const float spaceAboveChar = ascent + yCoord1;
    //         // SAVE
    //         const float characterYOffset = spaceAboveChar + currentY;
    //         // convert to screen units
    //         std::cout << character << " - Y offset: " << characterYOffset << std::endl;

    //         //const int byteOffset = currentX + static_cast<int>(roundf(leftSideBearing * scale));

    //         // Since this uses a single character for each texture, stride is just the width of the character
    //         const int stride = charWidth;
    //         stbtt_MakeCodepointBitmap(&font, texture.get(), charWidth, charHeight, stride, scale, scale, character);

    //         currentX += roundf(glpyhWidth * scale);
    //         std::cout << "currentX: " << currentX << std::endl;
    //     }

    //     const int kern = stbtt_GetCodepointKernAdvance(&font, character, text[i + 1]);
    //     currentX += roundf(kern * scale);
    //     std::cout << "currentX + glpyhWidth + kern: " << currentX << std::endl;
    // }

    PrintString(path, "Test");
}

void Text::PrintString(const std::string& path, const std::string& str)
{
    (void)str;

     std::ifstream stream(path);
    std::vector<unsigned char> fontData((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());


    // unsigned char* ttf_buffer = new unsigned char[1000000];
    // #pragma warning(suppress: 4996)
    // fread(ttf_buffer, 1, 1000000, fopen(path.c_str(), "rb"));

    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontData.data(), 0);

    std::cout << "Space ascii value: " << static_cast<int>(' ') << std::endl;

    constexpr int b_w = 512; /* bitmap width */
    constexpr int b_h = 128; /* bitmap height */
    constexpr int imageSize = b_w * b_h;
    constexpr int l_h = 128; /* line height */

    /* create a bitmap for the phrase */
    unsigned char* bitmap = new unsigned char[imageSize];

    /* calculate font scaling */
    const float scale = stbtt_ScaleForPixelHeight(&font, l_h);
    std::cout << "scale: " << scale << std::endl;

    int currentX = 0;
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);

    ascent = static_cast<int>(roundf(ascent * scale));
    descent = static_cast<int>(roundf(descent * scale));
    std::cout << "ascent: " << ascent << ", descent: " << descent << ", lineGap: " << lineGap << std::endl;

    for (int i = 0; i < str.length(); i++)
    {
        std::cout << "------- Character: " << str[i] << " --------" << std::endl;
        /* how wide is this character */
        int ax;
	    int lsb;
        stbtt_GetCodepointHMetrics(&font, str[i], &ax, &lsb);
        /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character str[i].) */
        std::cout << "ax: " << ax << ", lsb: " << lsb << std::endl;
        lsb = lsb;

        /* get bounding box for character (may be offset to account for chars that dip above or below the line) */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&font, str[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        // The visible pixels of the character, does not include empty space from the glyph
        const int charWidth = c_x2 - c_x1;
        const int charHeight = c_y2 - c_y1;

        std::cout << "coords: " << c_x1 << ", " << c_x2 << ", " << c_y1 << ", " << c_y2 << std::endl;

        /* compute spaceAboveChar (different characters have different heights) */
        int spaceAboveChar = ascent + c_y1;
        std::cout << "Pixels above char: " << spaceAboveChar << std::endl;

        if (str[i] == '\n')
        {
            std::cout << "Maths " << (ascent - descent + lineGap) * scale << " unscaled: " << (ascent - descent + lineGap) << std::endl;
            currentX = b_w * (ascent - descent + lineGap);
            std::cout << "New currentX: " << currentX << std::endl;
        }
        else
        {
            /* render character (stride and offset is important here) */
            int byteOffset = currentX + static_cast<int>(roundf(lsb * scale)) + (spaceAboveChar * b_w);
            // Stride is the width of the bitmap, because it needs to know how many bytes to skip to get to the next row
            stbtt_MakeCodepointBitmap(&font, bitmap + byteOffset, charWidth, charHeight, b_w, scale, scale, str[i]);
            std::cout << "byte offset: " << byteOffset << std::endl;

            /* advance currentX */
            std::cout << "currentX: " << currentX << std::endl;
            currentX += static_cast<int>(roundf(ax * scale));
            std::cout << "currentX + ax: " << currentX << std::endl;
        }


        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&font, str[i], str[i + 1]);
        std::cout << "kern: " << kern << std::endl;
        currentX += static_cast<int>(roundf(kern * scale));
        std::cout << "currentX + ax + kern: " << currentX << std::endl;
    }

    std::cout << "Total width: " << currentX << ", As percent: " << static_cast<float>(currentX) / static_cast<float>(b_w) * 100.0f << "%" << std::endl;

    // print out the bitmap
    // for (int i = 0; i < b_h * b_w; ++i)
    // {
    //     std::cout << static_cast<int>(bitmap[i]) << " ";

    //     if ((i + 1) % b_w == 0)
    //     {
    //         std::cout << std::endl;
    //     }
    // }

    /* save out a 1 channel image */
    stbi_write_png("out.png", b_w, b_h, 1, bitmap, b_w);
}

    // unsigned char ttf_buffer[100000];
    // #pragma warning(suppress: 4996)
    // fread(ttf_buffer, 1, 100000, fopen(path.c_str(), "rb"));
    // stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    // unsigned char mPixels[512 * 512];
    // stbtt_BakeFontBitmap(ttf_buffer, 0, static_cast<float>(size), mPixels, 512, 512, 31, 96, cdata);
    // stbi_write_png("image.png", 512, 512, 1, mPixels, 512);

void Text::PrintSingleCharacter(const std::string& path, char c)
{
    unsigned char ttf_buffer[100000];
    #pragma warning(suppress: 4996)
    fread(ttf_buffer, 1, 100000, fopen(path.c_str(), "rb"));

    stbtt_fontinfo font;
    stbtt_InitFont(&font, ttf_buffer, 0);

    std::cout << "Space ascii value: " << static_cast<int>(' ') << std::endl;

    const char character = c;
    const int lineHeight = 64;
    const int stride = 64;
    const float scale = stbtt_ScaleForPixelHeight(&font, lineHeight);

    int c_x1, c_y1, c_x2, c_y2;
    stbtt_GetCodepointBitmapBox(&font, character, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
    const int width = c_x2 - c_x1;
    const int height = c_y2 - c_y1;

    std::cout << "scale: " << scale << std::endl;
    std::cout << "coords: " << c_x1 << ", " << c_x2 << ", " << c_y1 << ", " << c_y2 << std::endl;

    unsigned char mPixels[512 * 512];
    stbtt_MakeCodepointBitmap(&font, mPixels, width, height, stride, scale, scale, character);

    stbi_write_png("image.png", width, height, 1, mPixels, stride);
}

} // namespace pong
