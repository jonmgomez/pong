#pragma once

#include "component.h"
#include "sound.h"

#include <glm/glm.hpp>

#include <chrono>
#include <functional>

namespace pong
{

class GameObject;

class Behavior : public Component<Behavior>
{
public:
    Behavior() = default;
    virtual ~Behavior() = default;

    virtual int GetBehaviorId() const = 0;
    virtual void Accept(ComponentDeserializer& /*visitor*/) override {};
    virtual void OnStart() {};
    virtual void OnUpdate() {};
    virtual void OnCollisionStart(GameObject& /*other*/) {};
    virtual void OnCollisionStay(GameObject& /*other*/) {};
    virtual void OnCollisionStop(GameObject& /*other*/) {};

    bool mOnStartCalled { false };
};

template<typename T>
int GetIdFromBehavior()
{
    return TypeIdGenerator<Behavior>::GetId<T>();
}

} // namespace pong
