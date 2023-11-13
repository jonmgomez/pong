#include "gameobject.h"

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
        mColliderBox->OnPositionUpdate(mPosition);
    }
}

std::string GameObject::GetInstanceName() const
{
    return mInstanceName;
}

void GameObject::SetInstanceName(const std::string& name)
{
    mInstanceName = name;
}

bool GameObject::CheckForCollision(GameObject& other)
{
    if (mColliderBox != nullptr && other.mColliderBox != nullptr)
    {
        return mColliderBox->CheckForCollision(*other.mColliderBox);
    }
    return false;
}

void GameObject::SetTimeout(std::chrono::duration<double> timeout, std::function<void()> callback)
{
    Pong::SetTimeout(GetId(), timeout, callback);
}

void GameObject::Render() const
{
    if (mMesh != nullptr)
    {
        mMesh->Draw(mPosition);
    }
}

} // namespace pong
