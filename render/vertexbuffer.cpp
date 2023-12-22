#include "vertexbuffer.h"

#include "renderutils.h"

namespace pong
{

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &mRendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    mSize = size;
}

VertexBuffer::VertexBuffer(unsigned int size)
{
    GLCall(glGenBuffers(1, &mRendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    mSize = size;
}

VertexBuffer::VertexBuffer(VertexBuffer&& other)
{
    mRendererId = other.mRendererId;
    mSize = other.mSize;
    other.mRendererId = 0;
    other.mSize = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
{
    if (this != &other)
    {
        mRendererId = other.mRendererId;
        mSize = other.mSize;
        other.mRendererId = 0;
        other.mSize = 0;
    }
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &mRendererId));
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
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

} // namespace pong
