#pragma once

namespace pong
{

class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(unsigned int size);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&);
    VertexBuffer& operator=(VertexBuffer&&);
    ~VertexBuffer();

    void SetBufferData(const void* data) const;
    void Bind() const;
    void Unbind() const;

private:
    unsigned mRendererId {0};
    unsigned int mSize {0};
};

} // namespace pong
