#pragma once

#include "indexbuffer.h"
#include "renderutils.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"

#include <memory>

namespace pong
{

class Renderer
{
private:
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    ~Renderer() = default;

    std::unique_ptr<Shader>mShader { nullptr };

public:
    static Renderer& GetInstance();

    static void SetShader(const std::string& filePath);
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const glm::vec3& position, const Texture& texture);
    static void Clear();
};

} // namespace pong
