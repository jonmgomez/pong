#include "gameobject.h"

#include "behavior.h"
#include "renderutils.h"
#include "pong.h"

namespace pong
{

int GameObject::sId = 0;

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

bool GameObject::ShouldDestroyOnLoad() const
{
    return mDestroyOnLoad;
}

void GameObject::SetDestroyOnLoad(const bool destroyOnLoad)
{
    mDestroyOnLoad = destroyOnLoad;
}

std::vector<Behavior*> GameObject::GetBehaviorComponents() const
{
    std::vector<Behavior*> behaviors {};

    const auto& allBehaviors = Behavior::GetComponents();

    for (auto& behavior : allBehaviors)
    {
        if (behavior->GetGameObjectId() == mId)
        {
            behaviors.push_back(behavior.get());
        }
    }

    return behaviors;
}

void GameObject::Destroy()
{
    for (auto& component : mComponents)
    {
        component.second->Destroy();
    }
}

} // namespace pong
