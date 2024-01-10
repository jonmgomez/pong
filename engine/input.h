#pragma once

#include "applicationwindow.h"
#include "renderer.h"

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
    Input(Renderer& renderer, ApplicationWindow& window);

    void Init();
    void Update();

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    InputState GetKeyState(unsigned int keycode);
    bool CheckKeyDown(unsigned int keycode);
    bool CheckKeyUp(unsigned int keycode);

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    InputState GetMouseButtonState(unsigned int button);
    bool CheckMouseButtonDown(unsigned int button);
    bool CheckMouseButtonUp(unsigned int button);

    void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    glm::vec3 GetMousePosition();

private:
    Renderer& mRenderer;
    ApplicationWindow& mWindow;
    std::array<InputState, GLFW_KEY_LAST + 1> mKeys {};
    std::array<InputState, GLFW_MOUSE_BUTTON_LAST + 1> mMouseButtons {};
    // Initalize way outside the screen so it does not trigger anything before it should
    glm::vec3 mMousePosition { std::numeric_limits<float>::max() };
};

} // namespace pong

namespace pong::input
{

extern Input* gInput;

Input* GetInputInstance();
void SetInputInstance(Input* input);

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);

InputState GetKeyState(unsigned int keycode);
bool CheckKeyDown(unsigned int keycode);
bool CheckKeyUp(unsigned int keycode);

InputState GetMouseButtonState(unsigned int button);
bool CheckMouseButtonDown(unsigned int button);
bool CheckMouseButtonUp(unsigned int button);

glm::vec3 GetMousePosition();

} // namespace pong::input
