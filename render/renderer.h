#pragma once

#include "indexbuffer.h"
#include "renderutils.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"

#include <memory>

namespace pong
{

static constexpr int SCREEN_WIDTH = 1280;
static constexpr int SCREEN_HEIGHT = 960;

class Renderer
{
public:
    static Renderer& GetInstance();

    static void Cleanup();
    static void SetShader(const std::string& filePath);
    static void Draw(const VertexArray& va, const IndexBuffer& ib,
                     const glm::vec3& position, const Texture& texture,
                     const GLRGBAColor& color);
    static void Clear();

    static float GetXScreenCoords();
    static float GetYScreenCoords();

private:
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    ~Renderer() = default;

    std::unique_ptr<Shader>mShader { nullptr };
    float mXScreenCoords { SCREEN_WIDTH };
    float mYScreenCoords { SCREEN_HEIGHT };
};

} // namespace pong
