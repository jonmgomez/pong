#pragma once

#include "indexbuffer.h"
#include "texture.h"
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

protected:
    VertexArray mVA {};
    VertexBuffer mVB {};
    IndexBuffer mIB {};
    std::unique_ptr<Texture>mTexture { nullptr };
};

} // namespace pong
