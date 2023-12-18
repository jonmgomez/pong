#include "component.h"

namespace pong
{

int BaseComponent::GetGameObjectID() const
{
    return mGameObjectID;
}

void BaseComponent::SetGameObjectID(int gameObjectID)
{
    mGameObjectID = gameObjectID;
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
