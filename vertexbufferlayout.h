#pragma once

#include "renderutils.h"

#include <vector>

namespace pong
{

struct VertexBufferElement
{
    unsigned int mType {0};
    unsigned int mCount {0};
    bool         mNormalized {false};

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
    std::vector<VertexBufferElement> mElements {};
    unsigned int mStride {0};

public:
    template<typename T>
    void Push(unsigned int count);
    const std::vector<VertexBufferElement>& GetElements() const;
    unsigned int GetStride() const;
};

} // namespace pong
