#include "vertexarray.h"

#include "renderutils.h"

#include <vector>

namespace pong
{

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &mRendererId));
}

VertexArray::VertexArray(VertexArray&& other) :
    mRendererId(other.mRendererId)
{
    other.mRendererId = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    if (this != &other)
    {
        mRendererId = other.mRendererId;
        other.mRendererId = 0;
    }
    return *this;
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &mRendererId));
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
    GLCall(glBindVertexArray(mRendererId));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

} // namespace pong
