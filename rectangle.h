#pragma once

#include <glm/glm.hpp>

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

class Rectangle
{
private:
    float mWidth;
    float mHeight;
    VertexBuffer mVB;
    VertexArray mVA;
    IndexBuffer mIB;
    Texture *mTexture;

public:
    Rectangle(const glm::vec3& position, float width, float height);
    Rectangle(float width, float height);
    ~Rectangle();

    void SetPosition(const glm::vec3& position);
    void Draw(const Renderer& renderer, Shader& shader) const;

    glm::vec3 mPosition;
};
