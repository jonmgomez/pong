#pragma once

class VertexBuffer
{
private:
    unsigned mRendererID {0};
    unsigned int mSize {0};
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(unsigned int size);
    ~VertexBuffer();

    void SetBufferData(const void* data) const;
    void Bind() const;
    void Unbind() const;
};
