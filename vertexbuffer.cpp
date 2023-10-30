#include "vertexbuffer.h"

#include "renderutils.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    mSize = size;
}

VertexBuffer::VertexBuffer(unsigned int size)
{
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    mSize = size;
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
    mRendererID = other.mRendererID;
    mSize = other.mSize;
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
    if (this != &other)
    {
        mRendererID = other.mRendererID;
        mSize = other.mSize;
    }
    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& other)
{
    mRendererID = other.mRendererID;
    mSize = other.mSize;
    other.mRendererID = 0;
    other.mSize = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
{
    if (this != &other)
    {
        mRendererID = other.mRendererID;
        mSize = other.mSize;
        other.mRendererID = 0;
        other.mSize = 0;
    }
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void VertexBuffer::SetBufferData(const void* data) const
{
    const unsigned int kOffset = 0;
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, kOffset, mSize, data));
    Unbind();
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
