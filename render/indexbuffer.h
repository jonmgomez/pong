#pragma once

namespace pong
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&);
    IndexBuffer& operator=(IndexBuffer&&);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;

private:
    unsigned int mRendererId {0};
    unsigned int mCount {0};
};

} // namespace pong
