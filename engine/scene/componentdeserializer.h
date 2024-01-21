#pragma once

#include "utils.h"

#include <nlohmann/json.hpp>

#include <unordered_map>

namespace pong
{

class BallMovement;
class BaseComponent;
class Behavior;
class Button;
class CheckBox;
class ColliderBox;
class Mesh;
class Player;
class Opponent;
class ScoreArea;
class ScoreController;
class SettingsScreenController;
class Slider;
class Text;
class TitleScreenController;
class Transform;

class ComponentDeserializer
{
public:
    void DeserializeComponent(BaseComponent* component, const nlohmann::json& json);
    void RegisterComponentId(BaseComponent* component, const int id);

    // Engine components
    void VisitComponent(Button* component);
    void VisitComponent(CheckBox* component);
    void VisitComponent(ColliderBox* component);
    void VisitComponent(Mesh* component);
    void VisitComponent(Slider* component);
    void VisitComponent(Text* component);
    void VisitComponent(Transform* component);


    void VisitComponent(Behavior* component);
    // User defined components
    void VisitComponent(Opponent* component);
    void VisitComponent(Player* component);
    void VisitComponent(BallMovement* component);
    void VisitComponent(ScoreArea* component);
    void VisitComponent(ScoreController* component);

private:
    template<typename T>
    T* FindComponent(const int id);

    nlohmann::json mCurrentJson;
    std::unordered_map<int, BaseComponent*> mComponents;
};

} // namespace pong

#include "component.h"
#include "behavior.h"

namespace pong
{

template<typename T>
T* ComponentDeserializer::FindComponent(const int id)
{
    auto it = mComponents.find(id);
    if (it == mComponents.end())
    {
        LogError("Component with id {} not found", id);
        ASSERT(false);
        return nullptr;
    }

    const int typeId = it->second->GetTypeId();
    if (GetComponentTypeId<T>() == typeId)
    {
        return static_cast<T*>(it->second);
    }
    else if (GetComponentTypeId<Behavior>() == typeId)
    {
        if (GetIdFromBehavior<T>() == static_cast<Behavior*>(it->second)->GetBehaviorId())
        {
            return static_cast<T*>(it->second);
        }
    }

    LogError("Component with id {} is not of correct type.", id);
    ASSERT(false);
    return nullptr;
}

} // namespace pong
