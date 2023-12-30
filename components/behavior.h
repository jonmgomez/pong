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
    void Accept(ComponentDeserializer& /*visitor*/) override {};
    virtual void OnStart() {};
    virtual void OnUpdate() {};
    virtual void OnCollisionStart(GameObject& /*other*/) {};
    virtual void OnCollisionStay(GameObject& /*other*/) {};
    virtual void OnCollisionStop(GameObject& /*other*/) {};

    void SetTimeout(const std::chrono::duration<double>& timeout, const std::function<void()>& callback);
    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);
};

template<typename T>
int GetIdFromBehavior()
{
    return TypeIdGenerator<Behavior>::GetId<T>();
}

} // namespace pong
