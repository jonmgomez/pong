#include "indexbuffer.h"

#include "renderutils.h"

namespace pong
{

// Ensure unsigned int is the same as a GLuint
static_assert(sizeof(unsigned int) == sizeof(GLuint));

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    mCount = count;
}

IndexBuffer::IndexBuffer(IndexBuffer&& other)
{
    mRendererID = other.mRendererID;
    mCount = other.mCount;
    other.mRendererID = 0;
    other.mCount = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
    if (this != &other)
    {
        mRendererID = other.mRendererID;
        mCount = other.mCount;
        other.mRendererID = 0;
        other.mCount = 0;
    }
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const
{
    return mCount;
}

} // namespace pong
