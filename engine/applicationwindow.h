#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace pong
{

class ApplicationWindow
{
public:
    ApplicationWindow() = default;
    ~ApplicationWindow() = default;

    void Init();
    void SwapBuffers();
    void Cleanup();

    int GetScreenWidth() const;
    int GetScreenHeight() const;
    void WindowResizeCallback(GLFWwindow* window, int width, int height);

    void SetWindowTitle(const std::string& title);
    void SetWindowIcon(const std::string& iconPath);

    bool ShouldClose() const;
    void SetShouldCloseWindow();

    bool IsVSyncActive() const;
    void SetVSync(bool active);

    GLFWwindow* GetWindow() const;

private:
    GLFWwindow* mWindow { nullptr };
    int mScreenWidth { 1280 };
    int mScreenHeight { 960 };
    bool mVSync { true };
};

} // namespace pong

namespace pong::application
{

extern ApplicationWindow* gApplicationWindow;

ApplicationWindow* GetWindowInstance();
void SetWindowInstance(ApplicationWindow* window);

void WindowResizeCallback(GLFWwindow* window, int width, int height);

int GetScreenWidth();
int GetScreenHeight();
void SetWindowTitle(const std::string& title);
void SetWindowIcon(const std::string& iconPath);
bool IsVSyncActive();
void SetVSync(bool active);

}
