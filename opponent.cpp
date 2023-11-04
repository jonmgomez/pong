#include "opponent.h"

#include "rectangle.h"

#include <glm/glm.hpp>

namespace pong
{

static constexpr float OPPONENT_WIDTH = 25.0f;
static constexpr float OPPONENT_HEIGHT = 225.0f;
static constexpr float OPPONENT_SPEED = 2.5f;
static constexpr glm::vec3 OPPONENT_POSITION(550.0f, 0.0f, 0.0f);

static constexpr float OPPONENT_MOVEMENT_UPPER_BOUND = 225.0f;
static constexpr float OPPONENT_MOVEMENT_LOWER_BOUND = -225.0f;

void Opponent::OnStart()
{
    mMesh = std::make_unique<Rectangle>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    mColliderBox = std::make_unique<ColliderBox>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    SetPosition(OPPONENT_POSITION);
    SetInstanceName("Opponent");
    mSpeed = OPPONENT_SPEED;
}

bool movingUp = true;

void Opponent::OnUpdate()
{
    glm::vec3 position = GetPosition();

    if (movingUp)
    {
        SetPosition(position + glm::vec3(0.0f, mSpeed, 0.0f));
    }
    else
    {
        SetPosition(position + glm::vec3(0.0f, -mSpeed, 0.0f));
    }

    if (position.y >= OPPONENT_MOVEMENT_UPPER_BOUND)
    {
        movingUp = false;
    }
    else if (position.y <= OPPONENT_MOVEMENT_LOWER_BOUND)
    {
        movingUp = true;
    }
}

} // namespace pong
