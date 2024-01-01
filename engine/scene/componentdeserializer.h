#pragma once

#include <nlohmann/json.hpp>

namespace pong
{

class Ball;
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
    void VisitComponent(Ball* component);
    void VisitComponent(ScoreArea* component);
    void VisitComponent(ScoreController* component);

private:
    nlohmann::json mCurrentJson;
};

} // namespace pong
