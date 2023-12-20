#include "behavior.h"

#include "audiomixer.h"
#include "pong.h"

namespace pong
{

void Behavior::SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback)
{
    Pong::GetInstance().GetTimer().AddTimer(GetGameObjectID(), timeout, callback);
}

void Behavior::PlaySound(const Sound& sound)
{
    Pong::GetInstance().GetAudioMixer().PlaySound(sound);
}

void Behavior::PlaySound(const Sound& sound, const glm::vec3& position)
{
    Pong::GetInstance().GetAudioMixer().PlaySound(sound, position);
}

} // namespace pong
