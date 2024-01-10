#include "player.h"

#include "gameobject.h"
#include "input.h"
#include "rectangle.h"
#include "timer.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

void Player::OnStart()
{
    mTransform = GetComponent<Transform>();
    ASSERT(mTransform != nullptr)
}

void Player::OnUpdate()
{
    mVelocity = glm::vec3(0.0f);

    if (globals::input::CheckKeyDown(GLFW_KEY_W))
    {
        mVelocity = glm::vec3(0.0f, mSpeed, 0.0f);
    }
    else if (globals::input::CheckKeyDown(GLFW_KEY_S))
    {
        mVelocity = glm::vec3(0.0f, -mSpeed, 0.0f);
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
