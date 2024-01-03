#include "fontbank.h"

#include "config.h"
#include "logger.h"
#include "utils.h"

#include <chrono>
#include <string>
#include <vector>

namespace pong
{

void FontBank::LoadFonts()
{
    const std::optional<nlohmann::json> fonts = Config::GetJsonValue("fonts");
    ASSERT(fonts.has_value());

    int fontCount = 0;
    for (const auto& font : fonts.value())
    {
        const std::string fontPath = font["path"];
        const std::string fontName = font["name"];

        Font font {};
        const auto timeNow = std::chrono::system_clock::now();
        if (font.LoadFont(fontName, fontPath))
        {
            fontCount++;
            mFonts[fontName] = std::move(font);

            const auto timeAfter = std::chrono::system_clock::now();
            LogDebug("Loaded font {} in {}ms", fontName, std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter - timeNow).count());
        }
        else
        {
            LogError("Failed to load font: {}", fontName);
            ASSERT(false);
        }
    }

    if (fontCount > 0)
    {
        LogInfo("Loaded {} fonts", fontCount);
    }
    else
    {
        LogError("No fonts loaded!");
        ASSERT(false);
        return;
    }

    // Set the default font text components will use. If not present use the first font loaded.
    const std::string defaultFontName = Config::GetValue<std::string>("default_font");
    mDefaultFont = GetFont(defaultFontName);
    if (mDefaultFont == nullptr)
    {
        mDefaultFont = &mFonts.begin()->second;
        if (defaultFontName.empty())
        {
            LogInfo("No default font specified, using {} as default", mDefaultFont->GetName());
        }
        else
        {
            LogWarning("Default font not found: {}, using {} as default", defaultFontName, mDefaultFont->GetName());
        }
    }
}

Font* FontBank::GetFont(const std::string& fontName)
{
    auto fontIt = mFonts.find(fontName);
    if (fontIt != mFonts.end())
    {
        return &fontIt->second;
    }

    return nullptr;
}

Font* FontBank::GetDefaultFont()
{
    return mDefaultFont;
}

} // namespace pong
