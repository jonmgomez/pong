#include "gameobject.h"

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

} // namespace pong
