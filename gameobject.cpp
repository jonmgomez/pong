#include "gameobject.h"

#include "renderutils.h"

void GameObject::Render()
{
    ASSERT(mMesh != nullptr);
    mMesh->Draw(mPosition);
}
