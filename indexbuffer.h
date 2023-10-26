#pragma once

class IndexBuffer
{
private:
    unsigned int mRendererID {0};
    unsigned int mCount {0};

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;
};
