#pragma once

#include "component.h"
#include "gameobject.h"

namespace pong
{

class Behavior : public Component<Behavior>
{
public:
    Behavior() = default;
    virtual ~Behavior() = default;

    virtual void OnStart() {};
    virtual void OnUpdate() {};
    virtual void OnCollisionStart(GameObject& /*other*/) {};
    virtual void OnCollisionStay(GameObject& /*other*/) {};
    virtual void OnCollisionStop(GameObject& /*other*/) {};

    void SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback);
    void PlaySound(const Sound& sound);
    void PlaySound(const Sound& sound, const glm::vec3& position);

protected:
    template <typename T>
    int GetBehaviorID() const { return TypeIDGenerator<Behavior>::GetID<T>(); }
};

template <typename T>
class BehaviorIDGenerator
{
    static int GetBehaviorID()
    {
        return TypeIDGenerator<Behavior>::GetID<T>();
    }
};

} // namespace pong
