#pragma once

#include "behavior.h"
#include "colliderbox.h"

#include <memory>
#include <vector>

namespace pong
{

class GameObject;

enum class CollisionType
{
    Start,
    Stay,
    Stop
};

struct CollisionPair
{
    int mFirstGameObjectId;
    int mSecondGameObjectId;
};

class CollisionManager
{
public:
    void ProcessCollisions(const std::vector<std::unique_ptr<ColliderBox>>& colliderBoxes);

private:
    void CallbackScripts(const std::vector<Behavior*>& scripts, CollisionType type, GameObject* otherGameObject);
    bool IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const;
    bool IsCollisionPairValid(const CollisionPair& pair, int firstGameObjectId, int secondGameObjectId) const;
    void RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId);

    bool CheckForCollision(ColliderBox& first, ColliderBox& second) const;

    std::vector<CollisionPair>mCurrentCollisions {};
};

} // namespace pong
