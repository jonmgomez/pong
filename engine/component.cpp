#include "component.h"

#include "gameobject.h"

namespace pong
{

int BaseComponent::GetGameObjectId() const
{
    return mGameObject->GetId();
}

GameObject* BaseComponent::GetGameObject() const
{
    return mGameObject;
}

void BaseComponent::SetGameObject(GameObject*gameObject)
{
    mGameObject = gameObject;
}

} // namespace pong
