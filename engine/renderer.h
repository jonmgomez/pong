#pragma once

#include "graphic.h"
#include "indexbuffer.h"
#include "mesh.h"
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
    static void DrawAll();
    static void Draw(const std::vector<OffsetGraphic>& graphics, const glm::vec3& position);
    static void Draw(const Graphic& graphic, const glm::vec3& position);
    static void Draw(const RenderData& renderData, const glm::vec3& position);
    static void Draw(const VertexArray& va, const IndexBuffer& ib,
                     const Texture& texture, const GLRGBAColor& color,
                     const glm::vec3& position);
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
