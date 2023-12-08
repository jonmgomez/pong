#include "applicationwindow.h"

#include "logger.h"
#include "utils.h"

#include <GLFW/glfw3.h>

namespace pong
{

static constexpr int SCREEN_WIDTH = 1280;
static constexpr int SCREEN_HEIGHT = 960;

void ApplicationWindow::Init()
{
    if (!glfwInit())
    {
        LogError("glfwInit() failure");
        ASSERT(false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* kMonitor = nullptr;
    GLFWwindow* kShare = nullptr;
    mWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong", kMonitor, kShare);
    if (mWindow == nullptr)
    {
        LogError("glfwCreateWindow() failure");
        glfwTerminate();
        ASSERT(false);
    }

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowAspectRatio(mWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwMakeContextCurrent(mWindow);

    LogInfo("Window created: {}x{}", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ApplicationWindow::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void ApplicationWindow::Cleanup()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

bool ApplicationWindow::ShouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}

void ApplicationWindow::SetShouldCloseWindow()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

bool ApplicationWindow::IsVSyncActive() const
{
    return mVSync;
}

void ApplicationWindow::SetVSync(bool active)
{
    mVSync = active;
    glfwSwapInterval(mVSync ? GLFW_TRUE : GLFW_FALSE);
}

GLFWwindow* ApplicationWindow::GetWindow() const
{
    return mWindow;
}

} // namespace pong
