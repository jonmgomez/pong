#pragma once

#include "vertexbuffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) :
    mRendererID(0)
{
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}