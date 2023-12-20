#include "gameobject.h"

#include "behavior.h"
#include "audiomixer.h"
#include "renderutils.h"
#include "pong.h"

namespace pong
{

int GameObject::sId = 0;


int GameObject::GetID() const
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

std::vector<Behavior*> GameObject::GetBehaviorComponents() const
{
    std::vector<Behavior*> behaviors {};

    const auto& allBehaviors = Behavior::GetComponents();

    for (auto& behavior : allBehaviors)
    {
        if (behavior->GetGameObjectID() == mId)
        {
            behaviors.push_back(behavior.get());
        }
    }

    return behaviors;
}

} // namespace pong
