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
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    void SetBufferData(const void* data) const;
    void Bind() const;
    void Unbind() const;
};
