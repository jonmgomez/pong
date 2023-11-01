#include "vertexbufferlayout.h"

#include "renderutils.h"

#include <vector>

namespace pong
{

template<typename T>
void VertexBufferLayout::Push(unsigned int count)
{
    static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    mElements.push_back({GL_FLOAT, count, false});
    mStride += count * sizeof(GLfloat);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    mElements.push_back({GL_UNSIGNED_INT, count, false});
    mStride += count * sizeof(GLuint);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    mElements.push_back({GL_UNSIGNED_BYTE, count, true});
    mStride += count * sizeof(GLubyte);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
    return mElements;
}

unsigned int VertexBufferLayout::GetStride() const
{
    return mStride;
}

} // namespace pong
