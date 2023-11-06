#include "opponent.h"

#include "pong.h"
#include "rectangle.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr float OPPONENT_WIDTH = 25.0f;
static constexpr float OPPONENT_HEIGHT = 225.0f;
static constexpr float OPPONENT_SPEED = 4.5f;
static constexpr glm::vec3 OPPONENT_POSITION(550.0f, 0.0f, 0.0f);

static constexpr float OPPONENT_MOVEMENT_UPPER_BOUND = 275.0f;
static constexpr float OPPONENT_MOVEMENT_LOWER_BOUND = -275.0f;

void Opponent::OnStart()
{
    mMesh = std::make_unique<Rectangle>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    mColliderBox = std::make_unique<ColliderBox>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    SetPosition(OPPONENT_POSITION);
    SetInstanceName("Opponent");
    mSpeed = OPPONENT_SPEED;
    mBall = Pong::FindGameObject<Ball>();
}

void Opponent::OnUpdate()
{
    glm::vec3 position = GetPosition();

    if (mBall != nullptr)
    {
        if (mBall->GetPosition().y > position.y)
        {
            position.y += mSpeed;
        }
        else if (mBall->GetPosition().y < position.y)
        {
            position.y -= mSpeed;
        }
        SetPosition(position);
    }
}

} // namespace pong
