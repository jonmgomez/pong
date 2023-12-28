#include "graphic.h"

namespace pong
{

const RenderData Graphic::GetRenderData() const
{
    return { mVA, mIB, mTexture, mColor };
}

void Graphic::SetColor(const GLRGBAColor& color)
{
    mColor = color;
}

bool Graphic::IsEnabled() const
{
    return mEnabled;
}

void Graphic::SetEnabled(bool enabled)
{
    mEnabled = enabled;
}

} // namespace pong
