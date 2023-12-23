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
    const auto GetPositionedBounds = [](ColliderBox& collider)
    {
        RectangleBounds bounds = collider.GetBounds();
        const Transform* transform = collider.GetComponent<Transform>();
        if (transform != nullptr)
        {
            bounds = bounds + transform->mPosition;
        }
        return bounds;
    };

    for (int index = 0; index < colliders.size(); index++)
    {
        auto& collider = colliders[index];

        for (int otherIndex = index + 1; otherIndex < colliders.size(); otherIndex++)
        {
            auto& otherCollider = colliders[otherIndex];
            const std::vector<Behavior*> scripts = collider->GetGameObject()->GetBehaviorComponents();
            const std::vector<Behavior*> otherScripts = otherCollider->GetGameObject()->GetBehaviorComponents();
            GameObject* gameObject = collider->GetGameObject();
            GameObject* otherGameObject = otherCollider->GetGameObject();

            const bool collision = CheckForCollision(*collider, *otherCollider);
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

bool CollisionManager::CheckForCollision(ColliderBox& first, ColliderBox& second) const
{
    const auto GetPositionedBounds = [](ColliderBox& collider)
    {
        RectangleBounds bounds = collider.GetBounds();
        const Transform* transform = collider.GetComponent<Transform>();
        if (transform != nullptr)
        {
            bounds = bounds + transform->mPosition;
        }
        return bounds;
    };

    RectangleBounds bounds = GetPositionedBounds(first);
    RectangleBounds otherBounds = GetPositionedBounds(second);

    // Check within both collider's bounds. This is due to the
    // possibility of the one collider ecompassing the other
    // If that occurs, the other collider's positions do not not appear
    // inside the bounds and would not register as collision

    for (const auto& position : otherBounds.mBounds)
    {
        if (bounds.CheckPointInBounds(position))
        {
            return true;
        }
    }

    for (const auto& position : bounds.mBounds)
    {
        if (otherBounds.CheckPointInBounds(position))
        {
            return true;
        }
    }

    return false;
}

} // namespace pong
