#pragma once

#include "gameobject.h"

#include <vector>


namespace pong
{

struct CollisionPair
{
    GameObject* mFirstGameObject;
    GameObject* mSecondGameObject;
};


class Pong
{
private:
    std::vector<std::unique_ptr<GameObject>>mGameObjects {};
    std::vector<std::vector<GameObject*>>mCheckedCollisions {};
    std::vector<std::vector<GameObject*>>mCurrentlyColliding {};
    std::vector<CollisionPair>mCurrentCollisions {};
    std::vector<CollisionPair>mCheckedCollisionsNew {};

    bool IsCheckedCollision(GameObject* firstGameObject, GameObject* secondGameObject) const;
    bool IsCurrentlyColliding(GameObject* firstGameObject, GameObject* secondGameObject) const;

public:
    void PongInit();
    void PongGameLoop();
    void CheckForCollisions();
    void RemoveGameObjectCollisionPair(GameObject* firstGameObject, GameObject* secondGameObject);
};

} // namespace pong
