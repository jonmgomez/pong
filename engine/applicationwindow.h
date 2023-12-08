#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pong
{

class ApplicationWindow
{
public:
    void Init();
    void SwapBuffers();
    void Cleanup();

    bool ShouldClose() const;
    void SetShouldCloseWindow();

    bool IsVSyncActive() const;
    void SetVSync(bool active);

    GLFWwindow* GetWindow() const;

private:
    GLFWwindow* mWindow { nullptr };
    bool mVSync { true };
};

} // namespace pong
