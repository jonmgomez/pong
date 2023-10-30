#include "opponent.h"

#include "rectangle.h"

#include <glm/glm.hpp>

static constexpr float OPPONENT_WIDTH = 25.0f;
static constexpr float OPPONENT_HEIGHT = 225.0f;
static constexpr float OPPONENT_SPEED = 2.5f;
static constexpr glm::vec3 OPPONENT_POSITION(550.0f, 0.0f, 0.0f);

static constexpr float OPPONENT_MOVEMENT_UPPER_BOUND = 225.0f;
static constexpr float OPPONENT_MOVEMENT_LOWER_BOUND = -225.0f;

void Opponent::OnStart()
{
    mMesh = std::make_unique<Rectangle>(OPPONENT_WIDTH, OPPONENT_HEIGHT);
    mPosition = OPPONENT_POSITION;
    mSpeed = OPPONENT_SPEED;
}

bool movingUp = true;

void Opponent::OnUpdate()
{
    if (movingUp)
    {
        mPosition.y += mSpeed;
    }
    else
    {
        mPosition.y -= mSpeed;
    }

    if (mPosition.y >= OPPONENT_MOVEMENT_UPPER_BOUND)
    {
        movingUp = false;
    }
    else if (mPosition.y <= OPPONENT_MOVEMENT_LOWER_BOUND)
    {
        movingUp = true;
    }
}
