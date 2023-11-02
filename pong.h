#pragma once

#include "gameobject.h"

#include <vector>


namespace pong
{

struct CollisionPair
{
    int mFirstGameObjectId;
    int mSecondGameObjectId;
};


class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    std::vector<std::vector<GameObject*>>mCheckedCollisions {};
    std::vector<std::vector<GameObject*>>mCurrentlyColliding {};
    std::vector<CollisionPair>mCurrentCollisions {};
    std::vector<CollisionPair>mCheckedCollisionsNew {};

    bool IsCheckedCollision(int firstGameObjectId, int secondGameObjectId) const;
    bool IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const;

public:
    void PongInit();
    void PongGameLoop();
    void CheckForCollisions();
    void RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId);
};

} // namespace pong
