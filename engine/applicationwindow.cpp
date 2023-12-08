#include "applicationwindow.h"

#include "logger.h"
#include "utils.h"

#include <GLFW/glfw3.h>

namespace pong
{

static constexpr int SCREEN_WIDTH = 1280;
static constexpr int SCREEN_HEIGHT = 960;

ApplicationWindow& ApplicationWindow::GetInstance()
{
    static ApplicationWindow instance;
    return instance;
}

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
    GetInstance().mWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong", kMonitor, kShare);
    if (GetInstance().mWindow == nullptr)
    {
        LogError("glfwCreateWindow() failure");
        glfwTerminate();
        ASSERT(false);
    }

    glfwSetFramebufferSizeCallback(GetInstance().mWindow, ApplicationWindow::WindowResizeCallback);
    glfwMakeContextCurrent(GetInstance().mWindow);
    SetVSync(true);

    LogInfo("Window created: {}x{}", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ApplicationWindow::SwapBuffers()
{
    glfwSwapBuffers(GetInstance().mWindow);
    glfwPollEvents();
}

void ApplicationWindow::Cleanup()
{
    glfwDestroyWindow(GetInstance().mWindow);
    glfwTerminate();
}

int ApplicationWindow::GetScreenWidth()
{
    return GetInstance().mScreenWidth;
}

int ApplicationWindow::GetScreenHeight()
{
    return GetInstance().mScreenHeight;
}

void ApplicationWindow::WindowResizeCallback(GLFWwindow* /*window*/, int width, int height)
{
    GetInstance().mScreenWidth = width;
    GetInstance().mScreenHeight = height;
    glViewport(0, 0, width, height);
}

bool ApplicationWindow::ShouldClose()
{
    return glfwWindowShouldClose(GetInstance().mWindow);
}

void ApplicationWindow::SetShouldCloseWindow()
{
    glfwSetWindowShouldClose(GetInstance().mWindow, GLFW_TRUE);
}

bool ApplicationWindow::IsVSyncActive()
{
    return GetInstance().mVSync;
}

void ApplicationWindow::SetVSync(bool active)
{
    GetInstance().mVSync = active;
    glfwSwapInterval(GetInstance().mVSync ? GLFW_TRUE : GLFW_FALSE);
}

GLFWwindow* ApplicationWindow::GetWindow() const
{
    return mWindow;
}

} // namespace pong
