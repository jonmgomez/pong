#include "gameobject.h"

#include "renderutils.h"

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

ColliderBox* GameObject::GetColliderBox() const
{
    return mColliderBox.get();
}

glm::vec3 GameObject::GetPosition() const
{
    return mPosition;
}

void GameObject::SetPosition(const glm::vec3& position)
{
    mPosition = position;

    if (mColliderBox != nullptr)
    {
        mColliderBox->UpdatePositionBounds(mPosition);
    }
}

const std::string& GameObject::GetName() const
{
    return mName;
}

void GameObject::SetName(const std::string& name)
{
    mName = name;
}

bool GameObject::CheckForCollision(GameObject& other)
{
    if (mColliderBox != nullptr && other.mColliderBox != nullptr)
    {
        return mColliderBox->CheckForCollision(*other.mColliderBox);
    }
    return false;
}

void GameObject::Render() const
{
    ASSERT(mMesh != nullptr);
    mMesh->Draw(mPosition);
}

} // namespace pong
