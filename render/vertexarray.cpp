#include "vertexarray.h"

#include "renderutils.h"

#include <vector>

namespace pong
{

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &mRendererID));
}

VertexArray::VertexArray(const VertexArray& other) :
    mRendererID(other.mRendererID)
{
}

VertexArray& VertexArray::operator=(const VertexArray& other)
{
    if (this != &other)
    {
        mRendererID = other.mRendererID;
    }
    return *this;
}

VertexArray::VertexArray(VertexArray&& other) :
    mRendererID(other.mRendererID)
{
    other.mRendererID = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    if (this != &other)
    {
        mRendererID = other.mRendererID;
        other.mRendererID = 0;
    }
    return *this;
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &mRendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const std::vector<VertexBufferElement>& elements = layout.GetElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++)
    {
        const VertexBufferElement element = elements[i];

        GLCall(glEnableVertexAttribArray(i));

        // Needed conversion incantation to suppress data loss warning
        auto offsetPointer = reinterpret_cast<const void *>(static_cast<uintptr_t>(offset));
        GLCall(glVertexAttribPointer(i, element.mCount, element.mType,
            element.mNormalized, layout.GetStride(), offsetPointer));

        offset += element.mCount * VertexBufferElement::GetSizeOfType(element.mType);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(mRendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

} // namespace pong
