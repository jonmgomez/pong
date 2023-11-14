#pragma once

namespace pong
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer(const IndexBuffer&);
    IndexBuffer& operator=(const IndexBuffer&);
    IndexBuffer(IndexBuffer&&);
    IndexBuffer& operator=(IndexBuffer&&);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;

private:
    unsigned int mRendererID {0};
    unsigned int mCount {0};
};

} // namespace pong
