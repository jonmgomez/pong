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
    std::vector<CollisionPair>mCurrentCollisions {};

    bool IsCurrentlyColliding(int firstGameObjectId, int secondGameObjectId) const;
    bool IsCollisionPairValid(const CollisionPair& pair, int firstGameObjectId, int secondGameObjectId) const;
    void RemoveGameObjectCollisionPair(int firstGameObjectId, int secondGameObjectId);

public:
    void PongInit();
    void PongGameLoop();
    void CheckForCollisions();
};

} // namespace pong
