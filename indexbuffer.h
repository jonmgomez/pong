#pragma once

class IndexBuffer
{
private:
    unsigned int mRendererID {0};
    unsigned int mCount {0};

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;
};
