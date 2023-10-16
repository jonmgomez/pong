#pragma once

#include "renderer.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
private:
    unsigned int mRendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};