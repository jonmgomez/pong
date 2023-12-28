#include "renderer.h"

#include "button.h"
#include "config.h"
#include "checkbox.h"
#include "gameobject.h"
#include "indexbuffer.h"
#include "logger.h"
#include "renderutils.h"
#include "slider.h"
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

Renderer& Renderer::GetInstance()
{
    static Renderer sInstance;
    return sInstance;
}

void Renderer::Init()
{
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

    GetInstance().mShader = std::make_unique<Shader>(shaderPath);
}

void Renderer::Cleanup()
{
    GetInstance().mShader.reset();
    GetInstance().mShader = nullptr;
}

void Renderer::DrawAll()
{
    const std::vector<std::unique_ptr<Mesh>>& meshes = Mesh::GetComponents();
    for (const auto& mesh : meshes)
    {
        glm::vec3 position(0.0f);

        const Transform* transform = mesh->GetGameObject()->GetComponent<Transform>();
        if (transform != nullptr)
        {
            position = transform->mPosition;
        }

        const RenderData renderData = mesh->GetRenderData();
        Renderer::Draw(renderData, position);
    }

    const auto RenderUIElement = [](auto& uiElement)
    {
        glm::vec3 position(0.0f);
        const Transform* transform = uiElement.GetComponent<Transform>();
        if (transform != nullptr)
        {
            position = transform->mPosition;
        }
        const std::vector<OffsetGraphic>& graphics = uiElement.GetRenderables();

        Renderer::Draw(position, graphics);
    };

    const std::vector<std::unique_ptr<Text>>& texts = Text::GetComponents();
    for (const auto& text : texts)
    {
        RenderUIElement(*text);
    }

    const std::vector<std::unique_ptr<CheckBox>>& checkBoxes = CheckBox::GetComponents();
    for (const auto& checkBox : checkBoxes)
    {
        RenderUIElement(*checkBox);
    }

    const std::vector<std::unique_ptr<Button>>& buttons = Button::GetComponents();
    for (const auto& button : buttons)
    {
        RenderUIElement(*button);
    }

    const std::vector<std::unique_ptr<Slider>>& sliders = Slider::GetComponents();
    for (const auto& slider : sliders)
    {
        RenderUIElement(*slider);
    }
}

void Renderer::Draw(const glm::vec3& position, const std::vector<OffsetGraphic>& graphics)
{
    for (const auto& graphic : graphics)
    {
        const RenderData renderData = graphic.mGraphic.GetRenderData();
        Draw(renderData, position + graphic.mOffset);
    }
}

void Renderer::Draw(const RenderData& renderData, const glm::vec3& position)
{
    Draw(renderData.mVA, renderData.mIB, position, renderData.mTexture, renderData.mColor);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
                    const glm::vec3& position, const Texture& texture,
                    const GLRGBAColor& color)
{
    va.Bind();
    ib.Bind();

    GetInstance().mShader->Bind();
    const glm::mat4 proj = glm::ortho(-SCREEN_X_COORDS, SCREEN_X_COORDS, -SCREEN_Y_COORDS, SCREEN_Y_COORDS, -1.0f, 1.0f);
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    const glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    const glm::mat4 mvp = proj * view * model;

    texture.Bind(0);
    GetInstance().mShader->SetUniform1i("uTexture", 0);
    GetInstance().mShader->SetUniform4f("uColor", color.r, color.g, color.b, color.a);
    GetInstance().mShader->SetUniformMat4f("uMVP", mvp);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

float Renderer::GetXCoordMax()
{
    return SCREEN_X_COORDS;
}

float Renderer::GetYCoordMax()
{
    return SCREEN_Y_COORDS;
}

} // namespace pong
