#include "gameobject.h"

#include "audiomixer.h"
#include "renderutils.h"
#include "pong.h"

namespace pong
{

int GameObject::sId = 0;

void GameObject::OnStart()
{
}

void GameObject::OnUpdate()
{
}

void GameObject::OnCollisionStart(GameObject& /*other*/)
{
}

void GameObject::OnCollisionStay(GameObject& /*other*/)
{
}

void GameObject::OnCollisionStop(GameObject& /*other*/)
{
}

int GameObject::GetId() const
{
    return mId;
}

std::string GameObject::GetInstanceName() const
{
    return mInstanceName;
}

void GameObject::SetInstanceName(const std::string& name)
{
    mInstanceName = name;
}

void GameObject::SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback)
{
    Pong::SetTimeout(GetId(), timeout, callback);
}

void GameObject::PlaySound(const Sound& sound)
{
    Pong::GetInstance().GetAudioMixer().PlaySound(sound);
}

void GameObject::PlaySound(const Sound& sound, const glm::vec3& position)
{
    Pong::GetInstance().GetAudioMixer().PlaySound(sound, position);
}

} // namespace pong
