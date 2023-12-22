#include "component.h"

namespace pong
{

int BaseComponent::GetGameObjectId() const
{
    return mGameObjectId;
}

void BaseComponent::SetGameObjectId(int gameObjectId)
{
    mGameObjectId = gameObjectId;
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
