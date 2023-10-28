#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"

#include <glm/glm.hpp>

void Player::OnStart()
{
    mMesh = std::make_unique<Rectangle>(25.0f, 225.0f);
    mPosition = glm::vec3(-550.0f, 0.0f, 0.0f);
    mSpeed = 2.5f;
}

void Player::OnUpdate()
{
    std::cout << "Player::OnUpdate()" << std::endl;
    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        std::cout << "W is pressed" << std::endl;
        mPosition.y += mSpeed;
    }
    else if (Input::IsKeyPressed(GLFW_KEY_S))
    {
        mPosition.y -= mSpeed;
    }

    std::cout << "Position x: " << mPosition.x << ", y: " << mPosition.y << std::endl;
}
