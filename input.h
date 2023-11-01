#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

namespace pong
{

class Input
{
private:
    static std::array<bool, 512>mKeys;
public:
    static bool IsKeyPressed(unsigned int keycode);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} // namespace pong
