#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"
#include "timer.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr float PLAYER_SPEED = 850.0f;
static constexpr glm::vec3 PLAYER_POSITION(-1125.0f, 0.0f, 0.0f);

void Player::OnStart()
{
    mMesh = std::make_unique<Rectangle>(PLAYER_WIDTH, PLAYER_HEIGHT);
    mColliderBox = std::make_unique<ColliderBox>(PLAYER_WIDTH, PLAYER_HEIGHT);
    SetPosition(PLAYER_POSITION);
    SetInstanceName("Player");
}

void Player::OnUpdate()
{
    mVelocity = glm::vec3(0.0f);

    if (Input::CheckKeyDown(GLFW_KEY_W))
    {
        mVelocity = glm::vec3(0.0f, PLAYER_SPEED, 0.0f);
    }
    else if (Input::CheckKeyDown(GLFW_KEY_S))
    {
        mVelocity = glm::vec3(0.0f, -PLAYER_SPEED, 0.0f);
    }

    SetPosition(GetPosition() + mVelocity * Timer::frameTime);
}

void Player::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName().find("Wall") != std::string::npos)
    {
        // Undo movement to stop from going through wall
        SetPosition(GetPosition() - mVelocity * Timer::frameTime);
    }
}

void Player::OnCollisionStay(GameObject& other)
{
    OnCollisionStart(other);
}

} // namespace pong
