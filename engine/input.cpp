#include "input.h"

#include "logger.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace pong
{

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 960;

// All keys are intalized to false, for not pressed
std::array<bool, GLFW_KEY_LAST + 1> Input::mKeys {};
std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> Input::mMouseButtons {};
// Initalize way outside the screen so it does not trigger anything before it should
glm::vec3 Input::mMousePosition { std::numeric_limits<float>::max() };

bool Input::IsKeyPressed(unsigned int keycode)
{
    return mKeys[keycode];
}

void Input::KeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
    // Ignore unrecognized keys
    if (key < 0)
        return;

    if (action == GLFW_PRESS)
        mKeys[key] = true;
    else if (action == GLFW_RELEASE)
        mKeys[key] = false;
}

// Mouse position converted to screen/world coordinates
glm::vec3 Input::GetMousePosition()
{
    return mMousePosition;
}

void Input::MousePositionCallback(GLFWwindow* /*window*/, double xPos, double yPos)
{
    const float x = static_cast<float>(xPos);
    const float y = static_cast<float>(yPos);

    constexpr float halfWindowWidth = WINDOW_WIDTH / 2.0f;
    constexpr float halfWindowHeight = WINDOW_HEIGHT / 2.0f;

    mMousePosition.x = (x < halfWindowWidth) ?
        (halfWindowWidth - x) * -2.0f : (x - halfWindowWidth) * 2.0f;
    // y coords are positive going down, so we need to invert them
    mMousePosition.y = (y <= halfWindowHeight) ?
        (halfWindowHeight - y) * 2.0f : (y - halfWindowHeight) * -2.0f;
}

bool Input::IsMouseButtonPressed(unsigned int button)
{
    return mMouseButtons[button];
}

void Input::MouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
    mMouseButtons[button] = (action == GLFW_PRESS);
}

} // namespace pong
