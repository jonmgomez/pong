#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <array>

namespace pong
{

// Reprsents the state of the key or mouse button on the current frame
enum class InputState
{
    Pressed,
    Held,
    Released,
    NotPressed
};

class Input
{
public:
    static void Init(GLFWwindow* window);
    static void Update();
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool IsKeyPressed(unsigned int keycode);
    static InputState GetKeyState(unsigned int keycode);
    static bool CheckKeyDown(unsigned int keycode);
    static bool CheckKeyUp(unsigned int keycode);

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static glm::vec3 GetMousePosition();
    static InputState GetMouseButtonState(unsigned int button);
    static bool CheckMouseButtonDown(unsigned int button);
    static bool CheckMouseButtonUp(unsigned int button);

private:
    static std::array<InputState, GLFW_KEY_LAST + 1> mKeys;
    static std::array<InputState, GLFW_MOUSE_BUTTON_LAST + 1> mMouseButtons;
    static glm::vec3 mMousePosition;
};

} // namespace pong
