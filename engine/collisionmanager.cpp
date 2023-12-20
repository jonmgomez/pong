#include "collisionmanager.h"

#include "gameobject.h"
#include "transform.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace pong
{

void CollisionManager::ProcessCollisions(const std::vector<std::unique_ptr<ColliderBox>>& colliders)
{
    for (int index = 0; index < colliders.size(); index++)
    {
        auto& collider = colliders[index];
        if (auto* transform = collider->GetGameObject()->GetComponent<Transform>(); transform != nullptr)
        {
            collider->OnPositionUpdate(transform->mPosition);
        }

        for (int otherIndex = index + 1; otherIndex < colliders.size(); otherIndex++)
        {
            auto& otherCollider = colliders[otherIndex];
            if (otherCollider->GetGameObject()->GetComponent<Transform>() != nullptr)
            {
                otherCollider->OnPositionUpdate(otherCollider->GetGameObject()->GetComponent<Transform>()->mPosition);
            }
            const bool collision = collider->CheckForCollision(*otherCollider);

            GameObject* gameObject = collider->GetGameObject();
            GameObject* otherGameObject = otherCollider->GetGameObject();
            const bool wereColliding = IsCurrentlyColliding(gameObject->GetID(), otherGameObject->GetID());

            if (collision && !wereColliding)
            {
                gameObject->OnCollisionStart(*otherGameObject);
                otherGameObject->OnCollisionStart(*gameObject);
                mCurrentCollisions.push_back({ gameObject->GetID(), otherGameObject->GetID() });
            }
            else if (collision)
            {
                gameObject->OnCollisionStay(*otherGameObject);
                otherGameObject->OnCollisionStay(*gameObject);
            }
            else if (wereColliding)
            {
                gameObject->OnCollisionStop(*otherGameObject);
                otherGameObject->OnCollisionStop(*gameObject);
                RemoveGameObjectCollisionPair(gameObject->GetID(), otherGameObject->GetID());
            }
        }
    }
}

bool CollisionManager::IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const
{
    if (std::any_of(std::begin(mCurrentCollisions), std::end(mCurrentCollisions),
        [&](const CollisionPair& collisionPair) { return IsCollisionPairValid(collisionPair, firstGameObjectId, secondGameObjectId); }))
    {
        return true;
    }
    return false;
}

bool CollisionManager::IsCollisionPairValid(const CollisionPair& pair, int firstGameObjectId, int secondGameObjectId) const
{
    return pair.mFirstGameObjectId == firstGameObjectId && pair.mSecondGameObjectId == secondGameObjectId
        || pair.mFirstGameObjectId == secondGameObjectId && pair.mSecondGameObjectId == firstGameObjectId;
}

void CollisionManager::RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId)
{
    mCurrentCollisions.erase(std::remove_if(mCurrentCollisions.begin(), mCurrentCollisions.end(),
        [&](const CollisionPair& collisionPair){ return IsCollisionPairValid(collisionPair, firstGameObjectId, secondGameObjectId); }),
        mCurrentCollisions.end());
}

} // namespace pong
