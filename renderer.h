#pragma once

#include "indexbuffer.h"
#include "shader.h"
#include "renderutils.h"
#include "vertexarray.h"

class Renderer
{
private:
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
