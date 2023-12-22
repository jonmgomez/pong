#include "indexbuffer.h"

#include "renderutils.h"

namespace pong
{

// Ensure unsigned int is the same as a GLuint
static_assert(sizeof(unsigned int) == sizeof(GLuint));

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    GLCall(glGenBuffers(1, &mRendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    mCount = count;
}

IndexBuffer::IndexBuffer(IndexBuffer&& other)
{
    mRendererId = other.mRendererId;
    mCount = other.mCount;
    other.mRendererId = 0;
    other.mCount = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
    if (this != &other)
    {
        mRendererId = other.mRendererId;
        mCount = other.mCount;
        other.mRendererId = 0;
        other.mCount = 0;
    }
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &mRendererId));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
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
