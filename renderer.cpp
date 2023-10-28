#include "renderer.h"

#include "indexbuffer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

std::unique_ptr<Renderer> Renderer::sInstance = std::make_unique<Renderer>();

void Renderer::SetShader(const std::string& filePath)
{
    sInstance->mShader = std::make_unique<Shader>(filePath);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const glm::vec3& position, const Texture& texture)
{
    va.Bind();
    ib.Bind();

    sInstance->mShader->Bind();
    const glm::mat4 proj = glm::ortho(-640.0f, 640.0f, -480.0f, 480.0f, -1.0f, 1.0f);
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    const glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    const glm::mat4 mvp = proj * view * model;

    texture.Bind(0);
    sInstance->mShader->SetUniform1i("u_Texture", 0);
    sInstance->mShader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    sInstance->mShader->SetUniformMat4f("u_MVP", mvp);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
