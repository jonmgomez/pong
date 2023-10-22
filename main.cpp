#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "indexbuffer.h"
#include "rectangle.h"
#include "renderer.h"
#include "renderutils.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    if (!glfwInit())
    {
        std::cout << "glfwInit() failure" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "glfwCreateWindow() failure" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Uncomment this if you would like to blow up the GPU :D
    // glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit() failure" << std::endl;
        return -1;
    }

    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    const float positions[] = {
        -200.0f, -183.5f, 0.0f, 0.0f,
         200.0f, -183.5f, 1.0f, 0.0f,
         200.0f,  183.5f, 1.0f, 1.0f,
        -200.0f,  183.5f, 0.0f, 1.0f
    };

    const unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;

    // Allocated and filled buffer on creation
    // VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    // Allocated buffer, filled later
    VertexBuffer vb(4 * 4 * sizeof(float));
    vb.SetBufferData(positions);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6);

    glm::mat4 proj = glm::ortho(-640.0f, 640.0f, -480.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::mat4 mvp =  proj * view * model;

    Shader shader = Shader("D:\\code\\pong\\basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    //Texture texture("D:\\code\\pong\\mc.png");
    // Texture texture("D:\\code\\pong\\white.png");
    //SolidColorTexture texture(255, 255, 255, 255);
    //texture.Bind(0);
    //shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    Rectangle rectangle(100.0f, 100.0f);

    // mark time
    double lastTime = glfwGetTime();
    int frameCount = 0;

    float r = 0.0f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.0f, 1.0f, 1.0f);

        //renderer.Draw(va, ib, shader);

        rectangle.Draw(renderer, shader);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;
        frameCount++;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    double currentTime = glfwGetTime();
    double elapsedTime = currentTime - lastTime;

    std::cout << "Elapsed time: " << elapsedTime << std::endl;
    std::cout << "Total frames: " << frameCount << std::endl;
    std::cout << "Avg framerate: " << frameCount / elapsedTime << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
