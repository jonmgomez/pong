#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

class PlayerBlueprint : public GameObjectBlueprint
{
public:
    PlayerBlueprint();
    void InitalizeComponents() override;
};

class Player : public Behavior
{
public:
    int GetBehaviorID() const override { return GetIDFromBehavior<Player>(); }
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

private:
    static constexpr float PLAYER_WIDTH = 15.0f;
    static constexpr float PLAYER_HEIGHT = 125.0f;

    Transform* mTransform { nullptr };
    glm::vec3 mVelocity { 0.0f };
    float mHeight { PLAYER_HEIGHT };
    float mWidth { PLAYER_WIDTH };
};

} // namespace pong
