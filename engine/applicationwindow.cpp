#include "applicationwindow.h"

#include "config.h"
#include "image.h"
#include "logger.h"
#include "utils.h"

#include <GLFW/glfw3.h>

namespace pong
{

using image::Image;

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

    glfwSetFramebufferSizeCallback(mWindow, application::WindowResizeCallback);
    glfwMakeContextCurrent(mWindow);
    SetVSync(Config::GetValue("vsync", false));

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

int ApplicationWindow::GetScreenWidth() const
{
    return mScreenWidth;
}

int ApplicationWindow::GetScreenHeight() const
{
    return mScreenHeight;
}

void ApplicationWindow::WindowResizeCallback(GLFWwindow* /*window*/, int width, int height)
{
    mScreenWidth = width;
    mScreenHeight = height;
    glViewport(0, 0, width, height);
}

void ApplicationWindow::SetWindowTitle(const std::string& title)
{
    glfwSetWindowTitle(mWindow, title.c_str());
}

void ApplicationWindow::SetWindowIcon(const std::string& iconPath)
{
    Image icon = image::LoadImage(iconPath);
    GLFWimage image = { icon.mWidth, icon.mHeight, icon.mPixels.data() };

    glfwSetWindowIcon(mWindow, 1, &image);
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
    Config::SetValue("vsync", active);
}

GLFWwindow* ApplicationWindow::GetWindow() const
{
    return mWindow;
}

} // namespace pong

namespace pong::application
{

ApplicationWindow* gApplicationWindow { nullptr };

ApplicationWindow* GetWindowInstance()
{
    return gApplicationWindow;
}

void SetWindowInstance(ApplicationWindow* window)
{
    gApplicationWindow = window;
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    GetWindowInstance()->WindowResizeCallback(window, width, height);
}

int GetScreenWidth()
{
    return GetWindowInstance()->GetScreenWidth();
}

int GetScreenHeight()
{
    return GetWindowInstance()->GetScreenHeight();
}

void SetWindowTitle(const std::string& title)
{
    GetWindowInstance()->SetWindowTitle(title);
}

void SetWindowIcon(const std::string& iconPath)
{
    GetWindowInstance()->SetWindowIcon(iconPath);
}

bool IsVSyncActive()
{
    return GetWindowInstance()->IsVSyncActive();
}

void SetVSync(bool active)
{
    GetWindowInstance()->SetVSync(active);
}

}