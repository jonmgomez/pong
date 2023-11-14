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
    ~VertexArray();
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;

private:
    unsigned int mRendererID {0};
};

} // namespace pong
