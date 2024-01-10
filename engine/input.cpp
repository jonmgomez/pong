#include "input.h"

#include "applicationwindow.h"
#include "renderer.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace pong
{

Input::Input(Renderer& renderer, ApplicationWindow& window) :
    mRenderer(renderer),
    mWindow(window)
{
}

void Input::Init()
{
    for (auto& inputVal : mKeys)
    {
        inputVal = InputState::NotPressed;
    }

    for (auto& inputVal : mMouseButtons)
    {
        inputVal = InputState::NotPressed;
    }

    GLFWwindow* glfwWindow = mWindow.GetWindow();
    glfwSetKeyCallback(glfwWindow, input::KeyCallback);
    glfwSetCursorPosCallback(glfwWindow, input::MousePositionCallback);
    glfwSetMouseButtonCallback(glfwWindow, input::MouseButtonCallback);
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

InputState Input::GetKeyState(unsigned int keycode)
{
    return mKeys[keycode];
}

bool Input::CheckKeyDown(unsigned int keycode)
{
    return mKeys[keycode] == InputState::Pressed || mKeys[keycode] == InputState::Held;
}

bool Input::CheckKeyUp(unsigned int keycode)
{
    return mKeys[keycode] == InputState::Released || mKeys[keycode] == InputState::NotPressed;
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

void Input::MousePositionCallback(GLFWwindow* /*window*/, double xPos, double yPos)
{
    const float x = static_cast<float>(xPos);
    const float y = static_cast<float>(yPos);

    const int windowWidth = mWindow.GetScreenWidth();
    const int windowHeight = mWindow.GetScreenHeight();
    const float halfWindowWidth = windowWidth / 2.0f;
    const float halfWindowHeight = windowHeight / 2.0f;

    const float mouseWindowX = (x < halfWindowWidth) ?
        (halfWindowWidth - x) * -2.0f : (x - halfWindowWidth) * 2.0f;
    // y coords are positive going down, so we need to invert them
    const float mouseWindowY = (y <= halfWindowHeight) ?
        (halfWindowHeight - y) * 2.0f : (y - halfWindowHeight) * -2.0f;

    mMousePosition.x = mouseWindowX / windowWidth * mRenderer.GetXCoordMax();
    mMousePosition.y = mouseWindowY / windowHeight * mRenderer.GetYCoordMax();
}

// Mouse position converted to screen/world coordinates
glm::vec3 Input::GetMousePosition()
{
    return mMousePosition;
}

} // namespace pong

namespace pong::input
{

Input* gInput = nullptr;

Input* GetInputInstance()
{
    ASSERT(gInput != nullptr);
    return gInput;
}

void SetInputInstance(Input* input)
{
    gInput = input;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GetInputInstance()->KeyCallback(window, key, scancode, action, mods);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    GetInputInstance()->MouseButtonCallback(window, button, action, mods);
}

void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    GetInputInstance()->MousePositionCallback(window, xpos, ypos);
}

InputState GetKeyState(unsigned int keycode)
{
    return GetInputInstance()->GetKeyState(keycode);
}

bool CheckKeyDown(unsigned int keycode)
{
    return GetInputInstance()->CheckKeyDown(keycode);
}

bool CheckKeyUp(unsigned int keycode)
{
    return GetInputInstance()->CheckKeyUp(keycode);
}

InputState GetMouseButtonState(unsigned int button)
{
    return GetInputInstance()->GetMouseButtonState(button);
}

bool CheckMouseButtonDown(unsigned int button)
{
    return GetInputInstance()->CheckMouseButtonDown(button);
}

bool CheckMouseButtonUp(unsigned int button)
{
    return GetInputInstance()->CheckMouseButtonUp(button);
}

glm::vec3 GetMousePosition()
{
    return GetInputInstance()->GetMousePosition();
}

} // namespace pong::input
