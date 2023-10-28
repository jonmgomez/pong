#pragma once

#include "gameobject.h"

class Player : public GameObject
{
private:
    float mSpeed { 0.0f };

public:
    void OnStart() override;
    void OnUpdate() override;
};
