#pragma once

#include "indexbuffer.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>

#include <memory>

class Mesh
{
protected:
    VertexArray mVA {};
    std::unique_ptr<VertexBuffer>mVB { nullptr };
    std::unique_ptr<IndexBuffer>mIB { nullptr };
    std::unique_ptr<Texture>mTexture { nullptr };

public:
    void Draw(const glm::vec3& position) const;
};
