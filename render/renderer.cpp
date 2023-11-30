#include "renderer.h"

#include "indexbuffer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace pong
{

static constexpr float SCREEN_X_COORDS = SCREEN_WIDTH;
static constexpr float SCREEN_Y_COORDS = SCREEN_HEIGHT;

Renderer& Renderer::GetInstance()
{
    static Renderer sInstance;
    return sInstance;
}

void Renderer::Cleanup()
{
    GetInstance().mShader.reset();
    GetInstance().mShader = nullptr;
}

void Renderer::SetShader(const std::string& filePath)
{
    GetInstance().mShader = std::make_unique<Shader>(filePath);
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
    GetInstance().mShader->SetUniform1i("u_Texture", 0);
    GetInstance().mShader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
    GetInstance().mShader->SetUniformMat4f("u_MVP", mvp);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

} // namespace pong
