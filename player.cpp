#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr float PLAYER_WIDTH = 25.0f;
static constexpr float PLAYER_HEIGHT = 225.0f;
static constexpr float PLAYER_SPEED = 2.5f;
static constexpr glm::vec3 PLAYER_POSITION(-550.0f, 0.0f, 0.0f);

void Player::OnStart()
{
    mMesh = std::make_unique<Rectangle>(PLAYER_WIDTH, PLAYER_HEIGHT);
    mPosition = PLAYER_POSITION;
    mSpeed = PLAYER_SPEED;
}

void Player::OnUpdate()
{
    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        mPosition.y += mSpeed;
    }
    else if (Input::IsKeyPressed(GLFW_KEY_S))
    {
        mPosition.y -= mSpeed;
    }

    std::cout << "Position x: " << mPosition.x << ", y: " << mPosition.y << std::endl;
}

} // namespace pong
