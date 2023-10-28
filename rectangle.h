#pragma once

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>

#include <array>
#include <memory>

static const std::array<unsigned int, 6> kIndicies[] = {
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
    IndexBuffer mIB { kIndicies->data(), static_cast<unsigned int>(kIndicies->size()) };
    std::unique_ptr<Texture>mTexture { nullptr };

public:
    Rectangle(const glm::vec3& position, float width, float height);
    Rectangle(float width, float height);

    void SetPosition(const glm::vec3& position);
    void Draw(const Renderer& renderer, Shader& shader) const;

    glm::vec3 mPosition { glm::vec3(0.0f) };
};
