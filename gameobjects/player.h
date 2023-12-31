#pragma once

#include "behavior.h"
#include "gameobject.h"
#include "transform.h"

#include <glm/glm.hpp>

namespace pong
{

class Player : public Behavior
{
public:
    int GetBehaviorId() const override { return GetIdFromBehavior<Player>(); }
    void Accept(ComponentDeserializer& visitor) override { visitor.VisitComponent(this); }
    void OnStart() override;
    void OnUpdate() override;
    void OnCollisionStart(GameObject& other) override;
    void OnCollisionStay(GameObject& other) override;

private:
    Transform* mTransform { nullptr };
    float mSpeed { 0.0f };
    glm::vec3 mVelocity { 0.0f };

    friend class ComponentDeserializer;
};

} // namespace pong
