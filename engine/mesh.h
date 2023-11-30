#pragma once

#include "indexbuffer.h"
#include "texture.h"
#include "renderutils.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>

#include <memory>

namespace pong
{

class Mesh
{
public:
    virtual void Draw(const glm::vec3& position) const;

    void SetColor(const GLRGBAColor& color);

protected:
    VertexArray mVA {};
    VertexBuffer mVB {};
    IndexBuffer mIB {};
    Texture mTexture {};
    GLRGBAColor mColor { 1.0f, 1.0f, 1.0f, 1.0f };
};

} // namespace pong
