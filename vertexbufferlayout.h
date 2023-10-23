#pragma once

#include <vector>

#include "renderutils.h"

struct VertexBufferElement
{
    unsigned int mType;
    unsigned int mCount;
    bool         mNormalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
            default:                return 0;
        }
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> mElements;
    unsigned int mStride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void Push(unsigned int count);
    const std::vector<VertexBufferElement>& GetElements() const;
    unsigned int GetStride() const;
};
