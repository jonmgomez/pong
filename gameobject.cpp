#include "gameobject.h"

#include "renderutils.h"

namespace pong
{

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

} // namespace pong
