#include "main.h"

#include "indexbuffer.h"
#include "player.h"
#include "rectangle.h"
#include "renderer.h"
#include "renderutils.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

//std::unique_ptr<Rectangle>player = nullptr;
bool upHeld = false;
bool downHeld = false;

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
    glfwSetKeyCallback(window, KeyCallback);

    // Uncomment this if you would like to blow up the GPU :D
    // glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit() failure" << std::endl;
        return -1;
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    int numTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &numTextureSlots);
    std::cout << "Texture Slots Available: " << numTextureSlots << std::endl;

    Renderer::SetShader("D:\\code\\pong\\basic.shader");

    Player player;
    player.OnStart();
    //const float playerSpeed = 2.5f;

    // mark time
    double lastTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        Renderer::Clear();

        player.OnUpdate();
        player.Render();

        // if (upHeld)
        //     player->mPosition.y += playerSpeed;

        // if (downHeld)
        //     player->mPosition.y -= playerSpeed;

        // player->DrawObject();

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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "Key: " << key << ", Scancode: " << scancode << ", Action: " << action << ", Mods: " << mods << std::endl;
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
        {
            upHeld = true;
            std::cout << "W pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE)
        {
            upHeld = false;
        }
    }

    if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
        {
            downHeld = true;
            std::cout << "S pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE)
        {
            downHeld = false;
        }
    }
}
