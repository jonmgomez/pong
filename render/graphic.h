#pragma once

#include "indexbuffer.h"
#include "texture.h"
#include "renderutils.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>

namespace pong
{

struct RenderData
{
    const VertexArray& mVA;
    const IndexBuffer& mIB;
    const Texture& mTexture;
    const GLRGBAColor mColor { RGBA_WHITE };
};

class Graphic
{
public:
    const RenderData GetRenderData() const;
    void SetColor(const GLRGBAColor& color);
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

protected:
    VertexArray mVA {};
    VertexBuffer mVB {};
    IndexBuffer mIB {};
    Texture mTexture {};
    GLRGBAColor mColor { RGBA_WHITE };
    bool mEnabled { true };
};

struct OffsetGraphic
{
    const Graphic& mGraphic;
    const glm::vec3 mOffset { 0.0f, 0.0f, 0.0f };

    OffsetGraphic(const Graphic& graphic, const glm::vec3& offset) :
        mGraphic(graphic),
        mOffset(offset)
    {
    }
};

} // namespace pong
