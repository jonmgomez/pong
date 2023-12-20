#pragma once

#include "colliderbox.h"
#include "gameobject.h"
#include "player.h"
#include "rectangle.h"
#include "transform.h"

#include <string>
#include <memory>
#include <vector>

namespace pong
{

using GameObjectCollection = std::vector<std::unique_ptr<GameObject>>;

class Scene
{
public:
    virtual void BuildScene() = 0;

    GameObjectCollection TransferGameObjects()
    {
        GameObjectCollection gameObjects = std::move(mGameObjects);
        std::cout << "Vector size" << mGameObjects.size() << std::endl;
        return gameObjects;
    }

protected:
    GameObject* NewObject()
    {
        mGameObjects.push_back(std::make_unique<GameObject>());
        return mGameObjects.back().get();
    }

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObjectBlueprint, T>>, typename... Args>
    GameObject* NewObjectFromBlueprint(Args&&... args)
    {
        mGameObjects.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return mGameObjects.back().get();
    }

    void SetPosition(GameObject* object, const glm::vec3& position)
    {
        Transform* transform = object->GetComponent<Transform>();
        ASSERT(transform != nullptr);
        transform->mPosition = position;
    }

    void SetName(GameObject* object, const std::string& name)
    {
        object->SetInstanceName(name);
    }

private:
    GameObjectCollection mGameObjects {};
};

} // namespace pong
