#include "opponent.h"

#include "rectangle.h"

#include <glm/glm.hpp>

void Opponent::OnStart()
{
    mMesh = std::make_unique<Rectangle>(25.0f, 225.0f);
    mPosition = glm::vec3(550.0f, 0.0f, 0.0f);
    mSpeed = 2.5f;
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

    if (mPosition.y >= 225.0f)
    {
        movingUp = false;
    }
    else if (mPosition.y <= -225.0f)
    {
        movingUp = true;
    }
}
