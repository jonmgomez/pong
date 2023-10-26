#pragma once

#include <glm/glm.hpp>

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

static const unsigned int kIndicies[] = {
    0, 1, 2,
    2, 3, 0
};

class Rectangle
{
private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };
    VertexBuffer mVB { 4 * 4 * sizeof(float) };
    VertexArray mVA {};
    IndexBuffer mIB { kIndicies, 6 };
    Texture *mTexture { nullptr };

public:
    Rectangle(const glm::vec3& position, float width, float height);
    Rectangle(float width, float height);
    ~Rectangle();

    void SetPosition(const glm::vec3& position);
    void Draw(const Renderer& renderer, Shader& shader) const;

    glm::vec3 mPosition { glm::vec3(0.0f) };
};
