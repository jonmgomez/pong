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
    mColliderBox = std::make_unique<ColliderBox>(PLAYER_WIDTH, PLAYER_HEIGHT);
    SetPosition(PLAYER_POSITION);
    mSpeed = PLAYER_SPEED;
    mName = "Player";
}

void Player::OnUpdate()
{
    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        SetPosition(GetPosition() + glm::vec3(0.0f, mSpeed, 0.0f));
    }
    else if (Input::IsKeyPressed(GLFW_KEY_S))
    {
        SetPosition(GetPosition() + glm::vec3(0.0f, -mSpeed, 0.0f));
    }
}

} // namespace pong
