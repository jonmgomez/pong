#pragma once

#include "renderutils.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

namespace pong
{

class VertexArray
{
public:
    VertexArray();
    VertexArray(const VertexArray&);
    VertexArray& operator=(const VertexArray&);
    VertexArray(VertexArray&&);
    VertexArray& operator=(VertexArray&&);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;

private:
    unsigned int mRendererID {0};
};

} // namespace pong
