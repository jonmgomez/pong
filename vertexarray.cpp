#include "vertexarray.h"

#include <vector>

#include "renderutils.h"

VertexArray::VertexArray() :
    mRendererID(0)
{
    GLCall(glGenVertexArrays(1, &mRendererID));
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

        GLCall(glVertexAttribPointer(i,
            element.mCount, element.mType, element.mNormalized,
            layout.GetStride(), reinterpret_cast<const void *>(static_cast<uintptr_t>(offset))));

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
