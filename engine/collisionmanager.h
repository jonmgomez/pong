#pragma once

#include "gameobject.h"

#include <memory>
#include <vector>

namespace pong
{

struct CollisionPair
{
    int mFirstGameObjectId;
    int mSecondGameObjectId;
};

class CollisionManager
{
public:
    void ProcessCollisions(const std::vector<std::unique_ptr<GameObject>>& gameObjects);

private:
    bool IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const;
    bool IsCollisionPairValid(const CollisionPair& pair, int firstGameObjectId, int secondGameObjectId) const;
    void RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId);

    std::vector<CollisionPair>mCurrentCollisions {};
};

} // namespace pong
