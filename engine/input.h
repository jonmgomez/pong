#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <array>

namespace pong
{

class Input
{
public:
    static bool IsKeyPressed(unsigned int keycode);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static glm::vec3 GetMousePosition();
    static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static bool IsMouseButtonPressed(unsigned int button);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
    static std::array<bool, GLFW_KEY_LAST + 1> mKeys;
    static std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mMouseButtons;
    static glm::vec3 mMousePosition;
};

} // namespace pong
