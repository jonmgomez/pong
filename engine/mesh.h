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
    Mesh() = default;
    Mesh(const Mesh&);
    Mesh& operator=(const Mesh&);
    Mesh(Mesh&&);
    Mesh& operator=(Mesh&&);

    virtual void Draw(const glm::vec3& position) const;

protected:
    VertexArray mVA {};
    VertexBuffer mVB {};
    IndexBuffer mIB {};
    Texture mTexture {};
};

} // namespace pong
