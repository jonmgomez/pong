#include "gameobject.h"

#include "renderutils.h"

namespace pong
{

int GameObject::sId = 0;

void GameObject::Render()
{
    ASSERT(mMesh != nullptr);
    mMesh->Draw(mPosition);
}

void GameObject::OnStart()
{
}

void GameObject::OnUpdate()
{
}

int GameObject::GetId() const
{
    return mId;
}

void GameObject::SetName(const std::string& name)
{
    mName = name;
}

const std::string& GameObject::GetName() const
{
    return mName;
}

} // namespace pong
