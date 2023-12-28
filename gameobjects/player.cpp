#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"
#include "timer.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr glm::vec3 PLAYER_POSITION(-1125.0f, 0.0f, 0.0f);
static constexpr float PLAYER_WIDTH = 15.0f;
static constexpr float PLAYER_HEIGHT = 125.0f;
static constexpr float PLAYER_SPEED = 850.0f;

PlayerBlueprint::PlayerBlueprint()
{
    SetInstanceName("Player");
    AddComponent<Transform>(PLAYER_POSITION);
    AddComponent<Mesh>(std::make_unique<Rectangle>(PLAYER_WIDTH, PLAYER_HEIGHT));
    AddComponent<ColliderBox>(PLAYER_WIDTH, PLAYER_HEIGHT);
    AddComponent<Player>();
}

void Player::OnStart()
{
    mTransform = GetComponent<Transform>();
    ASSERT(mTransform != nullptr)
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

    mTransform->mPosition += mVelocity * Timer::frameTime;
}

void Player::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName().find("Wall") != std::string::npos)
    {
        // Undo movement to stop from going through wall
        mTransform->mPosition -= mVelocity * Timer::frameTime;
    }
}

void Player::OnCollisionStay(GameObject& other)
{
    OnCollisionStart(other);
}

} // namespace pong
