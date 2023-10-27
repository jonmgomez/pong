#include "rectangle.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

Rectangle::Rectangle(const glm::vec3& position, float width, float height) :
    mPosition {position},
    mWidth {width},
    mHeight {height}
{
    float positions[] = {
        -mWidth / 2, -mHeight / 2, 0.0f, 0.0f,
         mWidth / 2, -mHeight / 2, 1.0f, 0.0f,
         mWidth / 2,  mHeight / 2, 1.0f, 1.0f,
        -mWidth / 2,  mHeight / 2, 0.0f, 1.0f
    };

    mVB.SetBufferData(positions);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVA.AddBuffer(mVB, layout);

    const unsigned char kColorValue = 255;
    mTexture = std::make_unique<SolidColorTexture>(kColorValue, kColorValue, kColorValue, kColorValue);
}

Rectangle::Rectangle(float width, float height) :
    Rectangle(glm::vec3(0.0f), width, height)
{
}

void Rectangle::SetPosition(const glm::vec3& position)
{
    mPosition = position;
}

void Rectangle::Draw(const Renderer& renderer, Shader& shader) const
{
    shader.Bind();

    glm::mat4 proj = glm::ortho(-640.0f, 640.0f, -480.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), mPosition);

    glm::mat4 mvp = proj * view * model;

    mTexture->Bind(0);
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    renderer.Draw(mVA, mIB, shader);
}
