#include "opponent.h"

#include "pong.h"
#include "rectangle.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr float OPPONENT_WIDTH = 15.0f;
static constexpr float OPPONENT_HEIGHT = 125.0f;
static constexpr float OPPONENT_SPEED = 6.0f;
static constexpr glm::vec3 OPPONENT_POSITION(1125.0f, 0.0f, 0.0f);

void Opponent::OnStart()
{
    mMesh = std::make_unique<Rectangle>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    mColliderBox = std::make_unique<ColliderBox>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    SetPosition(OPPONENT_POSITION);
    SetInstanceName("Opponent");
    mBall = Pong::FindGameObject<Ball>();
}

void Opponent::OnUpdate()
{
    glm::vec3 position = GetPosition();

    if (mBall != nullptr)
    {
        mVelocity = glm::vec3(0.0f);

        if (mBall->GetPosition().y > position.y)
        {
            mVelocity = glm::vec3(0.0f, OPPONENT_SPEED, 0.0f);
        }
        else if (mBall->GetPosition().y < position.y)
        {
            mVelocity = glm::vec3(0.0f, -OPPONENT_SPEED, 0.0f);
        }

        SetPosition(position + mVelocity);
    }
}

void Opponent::OnCollisionStart(GameObject& other)
{
    if (other.GetInstanceName() == "Wall")
    {
        // Undo movement to stop from going through wall
        SetPosition(GetPosition() - mVelocity);
    }
}

void Opponent::OnCollisionStay(GameObject& other)
{
    OnCollisionStart(other);
}

} // namespace pong
