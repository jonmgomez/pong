#include "rectangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "indexbuffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

static const unsigned int kIndicies[] = {
    0, 1, 2,
    2, 3, 0
};

Rectangle::Rectangle(const glm::vec3& position, float width, float height) :
    mPosition(position),
    mWidth(width),
    mHeight(height),
    mVB(4 * 4 * sizeof(float)),
    mVA(),
    mIB(kIndicies, 6),
    mTexture(nullptr)
{
    float positions[] = {
        -width / 2, -height / 2, 0.0f, 0.0f,
         width / 2, -height / 2, 1.0f, 0.0f,
         width / 2,  height / 2, 1.0f, 1.0f,
        -width / 2,  height / 2, 0.0f, 1.0f
    };

    mVB.SetBufferData(positions);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVA.AddBuffer(mVB, layout);

    mTexture = new SolidColorTexture(255, 255, 255, 255);
}

Rectangle::Rectangle(float width, float height) :
    Rectangle(glm::vec3(0.0f), width, height)
{
}

Rectangle::~Rectangle()
{
    delete mTexture;
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
