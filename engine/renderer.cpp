#include "renderer.h"

#include "config.h"
#include "gameobject.h"
#include "indexbuffer.h"
#include "logger.h"
#include "renderutils.h"
#include "text.h"
#include "texture.h"
#include "transform.h"
#include "vertexarray.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <memory>

namespace pong
{

static constexpr float SCREEN_X_COORDS = 1280;
static constexpr float SCREEN_Y_COORDS = 960;

void Renderer::Init(ComponentManager* componentManager)
{
    ASSERT(componentManager != nullptr);
    mComponentManager = componentManager;

    if (glewInit() != GLEW_OK)
    {
        LogError("glewInit() failure");
        ASSERT(false);
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    LogInfo("Using OpenGL version: {}", glVersion);

    int numTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextureSlots);
    LogDebug("Texture Slots Available: {}", numTextureSlots);


    const auto shaderKey = Config::GetJsonValue("shader");
    if (!shaderKey.has_value())
    {
        LogError("\"shader\" JSON key not found");
        ASSERT(false);
    }

    if (!shaderKey.value().is_string())
    {
        LogError("\"shader\" JSON key is not a string");
        ASSERT(false);
    }

    const std::string shaderPath = shaderKey.value();
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail())
    {
        LogError("Failed to open shader file: {}", shaderPath);
        ASSERT(false);
    }

    mShader = std::make_unique<Shader>(shaderPath);
}

void Renderer::Cleanup()
{
    mShader.reset();
    mShader = nullptr;
}

void Renderer::DrawAll()
{
    const std::vector<std::unique_ptr<Mesh>>& meshes = Mesh::GetComponents();
    for (const auto& mesh : meshes)
    {
        if (!mesh->IsEnabled())
            continue;

        glm::vec3 position(0.0f);

        const Transform* transform = mesh->GetGameObject()->GetComponent<Transform>();
        if (transform != nullptr)
        {
            position = transform->mPosition;
        }

        const RenderData renderData = mesh->GetRenderData();
        Renderer::Draw(renderData, position);
    }

    const std::vector<UIComponent*>& uiComponents = mComponentManager->GetUIComponents();
    for (const auto& uiComponent : uiComponents)
    {
        if (!uiComponent->IsEnabled())
            continue;

        const Transform* transform = uiComponent->GetBaseComponent()->GetComponent<Transform>();
        const glm::vec3 position = transform != nullptr ? transform->mPosition : glm::vec3(0.0f);
        const std::vector<OffsetGraphic>& graphics = uiComponent->GetRenderables();
        Renderer::Draw(graphics, position);
    }
}

void Renderer::Draw(const std::vector<OffsetGraphic>& graphics, const glm::vec3& position)
{
    for (const auto& graphic : graphics)
    {
        Draw(graphic.mGraphic, position + graphic.mOffset);
    }
}

void Renderer::Draw(const Graphic& graphic, const glm::vec3& position)
{
    if (graphic.IsEnabled())
    {
        const RenderData renderData = graphic.GetRenderData();
        Draw(renderData.mVA, renderData.mIB, renderData.mTexture, renderData.mColor, position);
    }
}

void Renderer::Draw(const RenderData& renderData, const glm::vec3& position)
{
    Draw(renderData.mVA, renderData.mIB, renderData.mTexture, renderData.mColor, position);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
                    const Texture& texture, const GLRGBAColor& color,
                    const glm::vec3& position)
{
    va.Bind();
    ib.Bind();

    mShader->Bind();
    const glm::mat4 proj = glm::ortho(-SCREEN_X_COORDS, SCREEN_X_COORDS, -SCREEN_Y_COORDS, SCREEN_Y_COORDS, -1.0f, 1.0f);
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    const glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    const glm::mat4 mvp = proj * view * model;

    texture.Bind(0);
    mShader->SetUniform1i("uTexture", 0);
    mShader->SetUniform4f("uColor", color.r, color.g, color.b, color.a);
    mShader->SetUniformMat4f("uMVP", mvp);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

float Renderer::GetXCoordMax() const
{
    return SCREEN_X_COORDS;
}

float Renderer::GetYCoordMax() const
{
    return SCREEN_Y_COORDS;
}

} // namespace pong
