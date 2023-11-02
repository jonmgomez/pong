#include "gameobject.h"

#include "renderutils.h"

namespace pong
{

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

void GameObject::OnCollisionEnd(GameObject& /*other*/)
{
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

bool GameObject::CheckForCollision(GameObject& other)
{
    if (mColliderBox != nullptr && other.mColliderBox != nullptr)
    {
        std::cout << "Checking Collision for " << GetName() << " and " << other.GetName() << std::endl;
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
