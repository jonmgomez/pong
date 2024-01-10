#pragma once

#include "componentmanager.h"
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
    Renderer() = default;
    ~Renderer() = default;

    void Init(ComponentManager* componentManager);
    void Cleanup();
    void DrawAll();
    void Draw(const std::vector<OffsetGraphic>& graphics, const glm::vec3& position);
    void Draw(const Graphic& graphic, const glm::vec3& position);
    void Draw(const RenderData& renderData, const glm::vec3& position);
    void Draw(const VertexArray& va, const IndexBuffer& ib,
                     const Texture& texture, const GLRGBAColor& color,
                     const glm::vec3& position);
    void Clear();

    // Returns the maximum X coordinate of the viewable screen (minimum in opposite direction)
    float GetXCoordMax() const;
    // Returns the maximum Y coordinate of the viewable screen (minimum in opposite direction)
    float GetYCoordMax() const;

private:
    ComponentManager* mComponentManager { nullptr };
    std::unique_ptr<Shader> mShader { nullptr };
};

} // namespace pong
