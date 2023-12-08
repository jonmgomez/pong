#include "input.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace pong
{

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 960;

// All keys are intalized to false, for not pressed
std::array<InputState, GLFW_KEY_LAST + 1> Input::mKeys {};
std::array<InputState, GLFW_MOUSE_BUTTON_LAST + 1> Input::mMouseButtons {};
// Initalize way outside the screen so it does not trigger anything before it should
glm::vec3 Input::mMousePosition { std::numeric_limits<float>::max() };

void Input::Init(GLFWwindow* window)
{
    for (auto& inputVal : mKeys)
    {
        inputVal = InputState::NotPressed;
    }

    for (auto& inputVal : mMouseButtons)
    {
        inputVal = InputState::NotPressed;
    }

    glfwSetKeyCallback(window, Input::KeyCallback);
    glfwSetCursorPosCallback(window, Input::MousePositionCallback);
    glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
}

void Input::Update()
{
    const auto updateInputState = [](auto& inputStatesArray)
    {
        for (auto& state : inputStatesArray)
        {
            if (state == InputState::Pressed)
            {
                state = InputState::Held;
            }
            else if (state == InputState::Released)
            {
                state = InputState::NotPressed;
            }
        }
    };

    updateInputState(mKeys);
    updateInputState(mMouseButtons);
}

void Input::KeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
    // Ignore unrecognized keys
    if (key < 0)
        return;

    mKeys[key] = (action == GLFW_PRESS || action == GLFW_REPEAT) ? InputState::Pressed : InputState::Released;
}

bool Input::CheckKeyDown(unsigned int button)
{
    return mKeys[button] == InputState::Pressed || mKeys[button] == InputState::Held;
}

bool Input::CheckKeyUp(unsigned int button)
{
    return mKeys[button] == InputState::Released || mKeys[button] == InputState::NotPressed;
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

void Input::MouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
    mMouseButtons[button] = (action == GLFW_PRESS) ? InputState::Pressed : InputState::Released;
}

InputState Input::GetMouseButtonState(unsigned int button)
{
    return mMouseButtons[button];
}

bool Input::CheckMouseButtonDown(unsigned int button)
{
    return mMouseButtons[button] == InputState::Pressed || mMouseButtons[button] == InputState::Held;
}

bool Input::CheckMouseButtonUp(unsigned int button)
{
    return mMouseButtons[button] == InputState::Released || mMouseButtons[button] == InputState::NotPressed;
}

} // namespace pong
