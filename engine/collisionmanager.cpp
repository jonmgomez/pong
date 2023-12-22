#include "collisionmanager.h"

#include "behavior.h"
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

            std::vector<Behavior*> scripts = collider->GetGameObject()->GetBehaviorComponents();
            std::vector<Behavior*> otherScripts = otherCollider->GetGameObject()->GetBehaviorComponents();
            GameObject* gameObject = collider->GetGameObject();
            GameObject* otherGameObject = otherCollider->GetGameObject();
            const bool wereColliding = IsCurrentlyColliding(gameObject->GetId(), otherGameObject->GetId());

            if (collision && !wereColliding)
            {
                CallbackScripts(scripts, CollisionType::Start, otherGameObject);
                CallbackScripts(otherScripts, CollisionType::Start, gameObject);
                mCurrentCollisions.push_back({ gameObject->GetId(), otherGameObject->GetId() });
            }
            else if (collision)
            {
                CallbackScripts(scripts, CollisionType::Stay, otherGameObject);
                CallbackScripts(otherScripts, CollisionType::Stay, gameObject);
            }
            else if (wereColliding)
            {
                CallbackScripts(scripts, CollisionType::Stop, otherGameObject);
                CallbackScripts(otherScripts, CollisionType::Stop, gameObject);
                RemoveGameObjectCollisionPair(gameObject->GetId(), otherGameObject->GetId());
            }
        }
    }
}

void CollisionManager::CallbackScripts(const std::vector<Behavior*>& scripts, CollisionType collision, GameObject* gameObject)
{
    for (auto& script : scripts)
    {
        switch (collision)
        {
        case CollisionType::Start:
            script->OnCollisionStart(*gameObject);
            break;
        case CollisionType::Stay:
            script->OnCollisionStay(*gameObject);
            break;
        case CollisionType::Stop:
            script->OnCollisionStop(*gameObject);
            break;
        }
    }
};

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
