#pragma once

class VertexBuffer
{
private:
    unsigned mRendererID;
    unsigned int mSize;
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(unsigned int size);
    ~VertexBuffer();

    void SetBufferData(const void* data) const;
    void Bind() const;
    void Unbind() const;
};
