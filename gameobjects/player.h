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
};

class Player : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<Player>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

    void SetSpeed(float speed);

private:
    Transform* mTransform { nullptr };
    float mSpeed { 0.0f };
    glm::vec3 mVelocity { 0.0f };
};

} // namespace pong
