#include "input.h"

#include <GLFW/glfw3.h>

#include <iostream>

std::array<bool, 512> Input::mKeys{ false };

bool Input::IsKeyPressed(unsigned int keycode)
{
    return mKeys[keycode];
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Suppress unused parameter warnings
    (void)window;
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS)
        mKeys[key] = true;
    else if (action == GLFW_RELEASE)
        mKeys[key] = false;
}
