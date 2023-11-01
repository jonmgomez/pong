#include "input.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace pong
{

// All keys are intalized to false, for not pressed
std::array<bool, 512> Input::mKeys{};

bool Input::IsKeyPressed(unsigned int keycode)
{
    return mKeys[keycode];
}

void Input::KeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
    std::cout << "KeyCallback() key: " << key << ", action: " << action << std::endl;

    // Ignore unrecognized keys
    if (key < 0)
        return;

    if (action == GLFW_PRESS)
        mKeys[key] = true;
    else if (action == GLFW_RELEASE)
        mKeys[key] = false;
}

} // namespace pong
