#include "player.h"

#include "gameobject.h"
#include "rectangle.h"

#include <glm/glm.hpp>

void Player::OnStart()
{
    mMesh = std::make_unique<Rectangle>(25.0f, 225.0f);
    mPosition = glm::vec3(-550.0f, 0.0f, 0.0f);
}

void Player::OnUpdate()
{
    // if (Input::IsKeyPressed(GLFW_KEY_W))
    // {
    //     mPosition.y += mSpeed;
    // }
    // else if (Input::IsKeyPressed(GLFW_KEY_S))
    // {
    //     mPosition.y -= mSpeed;
    // }
}
