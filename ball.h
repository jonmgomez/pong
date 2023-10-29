#pragma once

#include "gameobject.h"

class Ball : public GameObject
{
private:
    float mSpeed { 0.0f };

public:
    void OnStart() override;
    void OnUpdate() override;
};
