#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pong
{

class ApplicationWindow
{
public:
    static ApplicationWindow& GetInstance();

    static void Init();
    static void SwapBuffers();
    static void Cleanup();

    static bool ShouldClose();
    static void SetShouldCloseWindow();

    static bool IsVSyncActive();
    static void SetVSync(bool active);

    GLFWwindow* GetWindow() const;

private:
    ApplicationWindow() = default;
    ~ApplicationWindow() = default;
    ApplicationWindow(const ApplicationWindow&) = delete;
    ApplicationWindow& operator=(const ApplicationWindow&) = delete;
    ApplicationWindow(ApplicationWindow&&) = delete;
    ApplicationWindow& operator=(ApplicationWindow&&) = delete;

    GLFWwindow* mWindow { nullptr };
    bool mVSync { true };
};

} // namespace pong
