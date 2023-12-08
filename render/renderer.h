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
public:
    static Renderer& GetInstance();

    static void Init();
    static void Cleanup();
    static void Draw(const VertexArray& va, const IndexBuffer& ib,
                     const glm::vec3& position, const Texture& texture,
                     const GLRGBAColor& color);
    static void Clear();

    // Returns the maximum X coordinate of the viewable screen (minimum in opposite direction)
    static float GetXCoordMax();
    // Returns the maximum Y coordinate of the viewable screen (minimum in opposite direction)
    static float GetYCoordMax();

private:
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    ~Renderer() = default;

    std::unique_ptr<Shader>mShader { nullptr };
};

} // namespace pong
