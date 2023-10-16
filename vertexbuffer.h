#pragma once

class VertexBuffer
{
private:
    unsigned mRendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};
