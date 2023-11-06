#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr glm::vec3 PLAYER_POSITION(-550.0f, 0.0f, 0.0f);

void Player::OnStart()
{
    mMesh = std::make_unique<Rectangle>(PLAYER_WIDTH, PLAYER_HEIGHT);
    mColliderBox = std::make_unique<ColliderBox>(PLAYER_WIDTH, PLAYER_HEIGHT);
    SetPosition(PLAYER_POSITION);
    SetInstanceName("Player");
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
